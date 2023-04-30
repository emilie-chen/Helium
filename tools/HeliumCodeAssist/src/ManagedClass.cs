using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace Helium;

internal enum AccessModifier
{
    Public,
    Private,
    Protected
}

internal struct FieldData
{
    public string type;
    public string name;
}

internal struct PropertyData
{
    public string type;
    public string name;
    public AccessModifier accessModifier;
    public bool hasGetter;
    public bool hasSetter;
    public bool isAutoProperty;
    public bool isGetterConst;
}

internal struct MethodData
{
    public MethodData()
    {
    }

    public string name;
    public string returnType;
    public bool isConst;
    public List<FieldData> parameters = new List<FieldData>();
}

internal struct ManagedClassData
{
    public ManagedClassData()
    {
    }

    public string typeName;
    public string baseTypeName;
    public List<MethodData> methods = new List<MethodData>();
    public List<PropertyData> properties = new List<PropertyData>();
}

internal static partial class Program
{
    private const string CLASS_HEADER_TEMPLATE = """
#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

class $typeName : public $baseTypeName
{
#pragma region Generated
#pragma endregion

};

heliumEnd

""";

    private const string CLASS_SOURCE_TEMPLATE = """
#include "Helium/HeliumPrecompiled.h"

#include "$header"
#include "Helium/Reflection/PropertyType.h"

heliumBegin

#pragma region Generated
#pragma endregion

heliumEnd

""";

    private static bool IsAutoProperty(this PropertyInfo prop)
    {
        return prop.CanRead && prop.CanWrite && prop.DeclaringType.GetFields(BindingFlags.NonPublic | BindingFlags.Instance)
                             .Any(f => f.Name.Contains("<" + prop.Name + ">"));
    }

    private static ManagedClassData ParseType(Type type)
    {
        ManagedClassData data = new ManagedClassData();
        data.typeName = type.Name;
        data.baseTypeName = type.BaseType.Name;
        foreach (PropertyInfo info in type.GetProperties(BindingFlags.Public | BindingFlags.Instance))
        {
            data.properties.Add(new PropertyData
            {
                type = info.PropertyType.Name,
                name = info.Name,
                accessModifier = AccessModifier.Public,
                hasGetter = info.CanRead,
                hasSetter = info.CanWrite,
                isAutoProperty = info.IsAutoProperty(),
                isGetterConst = info.CanRead && info.GetGetMethod().GetCustomAttribute<ConstAttribute>() != null
            });
        }


        return data;
    }

    private static void ProcessManagedClass(Type t)
    {
        ManagedClassData typeData = ParseType(t);
        NativePathAttribute pathAttribute = t.GetCustomAttribute<NativePathAttribute>();
        string path = $"src/{pathAttribute.path}";
        string headerPath = path + ".h";
        string sourcePath = path + ".cpp";
        string declarationPath = path + ".declaration.cs";
        if (!File.Exists(headerPath) && !File.Exists(sourcePath))
        {
            File.WriteAllText(headerPath, CLASS_HEADER_TEMPLATE.Replace("$typeName", typeData.typeName).Replace("$baseTypeName", typeData.baseTypeName));
            File.WriteAllText(sourcePath, CLASS_SOURCE_TEMPLATE.Replace("$header", Path.GetFileName(headerPath)));
        }

        ProcessManagedClassHeader(headerPath, typeData);
        ProcessManagedClassSource(sourcePath, typeData);
    }

    private static PropertyType ParsePropertyType(string name)
    {
        switch (name)
        {
            case "U8":
                return PropertyType.U8;
            case "U16":
                return PropertyType.U16;
            case "U32":
                return PropertyType.U32;
            case "U64":
                return PropertyType.U64;
            case "S8":
                return PropertyType.S8;
            case "S16":
                return PropertyType.S16;
            case "S32":
                return PropertyType.S32;
            case "S64":
                return PropertyType.S64;
            case "F32":
                return PropertyType.F32;
            case "F64":
                return PropertyType.F64;
            case "Bool":
                return PropertyType.Bool;
            case "Char":
                return PropertyType.Char;
            case "String":
                return PropertyType.String;
            case "vec2":
                return PropertyType.Vec2;
            case "vec3":
                return PropertyType.Vec3;
            case "vec4":
                return PropertyType.Vec4;
            case "quat":
                return PropertyType.Quat;
            case "mat4":
                return PropertyType.Mat4;
            case "mat3":
                return PropertyType.Mat3;
        }

        if (name.StartsWith("Handle"))
        {
            return PropertyType.Handle;
        }

        if (Type.GetType($"Helium.{name}").IsEnum)
        {
            return PropertyType.Enum;
        }

        return PropertyType.Invalid;
    }

    private static void ProcessManagedClassSource(string sourcePath, ManagedClassData typeData)
    {
        List<string> linesModified = new List<string>();
        string[] lines = File.ReadAllLines(sourcePath);

        int generatedRegionStart = SeekRegionStart(lines, "Generated");
        if (generatedRegionStart == -1)
        {
            Console.WriteLine("Generated region not found for type " + typeData.typeName);
            return;
        }

        int lineIndex = 0;
        bool codeGenCompleted = false;
        while (true)
        {
            if (lineIndex >= lines.Length)
            {
                break;
            }

            if (lineIndex <= generatedRegionStart || codeGenCompleted)
            {
                linesModified.Add(lines[lineIndex]);
                lineIndex++;
                continue;
            }

            // insert generated code
            linesModified.Add($"void {typeData.typeName}::RegisterMembers()");
            linesModified.Add("{");
            linesModified.Add("    UnsafeHandle<ManagedClassDescriptor> descriptor = GetClassDescriptor();");
            foreach (PropertyData property in typeData.properties)
            {
                linesModified.Add("""
    descriptor->AddProperty(nameof($propertyName), PropertyType::$propertyType,
    [](Handle<ManagedObject> instance)
    {
    	return $optionalTypeErasedCast instance.As<$typeName>()->$getterName();
    },
    $setterOptional,
    $typeDescriptor);
"""
                .Replace("$setterOptional", property.hasSetter ?
                """
                [](Handle<ManagedObject> instance, std::any value)
                    {
                    	instance.As<$typeName>()->$setterName($setterOptionalTypeErasure);
                    }
                """ : "std::nullopt")
                .Replace("$typeName", typeData.typeName)
                .Replace("$propertyName", property.name)
                .Replace("$propertyType", ParsePropertyType(property.type).ToString())
                .Replace("$getterName", $"Get{property.name}")
                .Replace("$setterName", $"Set{property.name}")
                .Replace("$setterOptionalTypeErasure", ParsePropertyType(property.type) == PropertyType.Enum ? "static_cast<$propertyNativeType>(std::any_cast<U64>(value))" : "std::any_cast<$propertyNativeType>(value)")
                .Replace("$optionalTypeErasedCast", ParsePropertyType(property.type) == PropertyType.Enum ? "(U64)" : "")
                .Replace("$propertyNativeType", property.type)
                .Replace("$typeDescriptor", ParsePropertyType(property.type) == PropertyType.Handle ? $"{property.type}::GetClassDescriptor()" : (
                    ParsePropertyType(property.type) == PropertyType.Enum ? $"{property.type}Helper::GetDescriptor()" : "nullptr"
                )));
            }
            linesModified.Add("}");

            codeGenCompleted = true;
            lineIndex = SeekRegionEnd(lines, "Generated");
        }

        File.WriteAllLines(sourcePath, linesModified);
    }

    private static void ProcessManagedClassHeader(string headerPath, ManagedClassData typeData)
    {
        List<string> headerLinesModified = new List<string>();
        string[] headerLines = File.ReadAllLines(headerPath);

        int managedPropertiesRegionStart = SeekRegionStart(headerLines, "Generated");
        if (managedPropertiesRegionStart == -1)
        {
            Console.WriteLine("Generated region not found for type " + typeData.typeName);
            return;
        }

        int headerLineIndex = 0;
        bool codeGenCompleted = false;
        while (true)
        {
            if (headerLineIndex >= headerLines.Length)
            {
                break;
            }

            if (headerLineIndex <= managedPropertiesRegionStart || codeGenCompleted)
            {
                headerLinesModified.Add(headerLines[headerLineIndex]);
                headerLineIndex++;
                continue;
            }


            // insert properties

            headerLinesModified.Add($"    MANAGED_CLASS({typeData.typeName}, {typeData.baseTypeName}, false);");

            headerLinesModified.Add("public:");

            foreach (PropertyData property in typeData.properties)
            {
                if (property.isAutoProperty)
                {
                    string backingFieldName = "m_" + property.name;
                    string backingFieldLine = $"private:\n    {property.type} {backingFieldName};";
                    string setterLine = $"public:\n    void Set{property.name}(const {property.type}& value) {{ {backingFieldName} = value; }}";
                    string getterLine = $"public:\n    {property.type} Get{property.name}() const {{ return {backingFieldName}; }}";
                    headerLinesModified.Add(backingFieldLine);
                    headerLinesModified.Add(setterLine);
                    headerLinesModified.Add(getterLine);
                }
                else
                {
                    if (property.hasSetter)
                    {
                        string setterLine = $"public:\n    void Set{property.name}(const {property.type}& value);";
                        headerLinesModified.Add(setterLine);
                    }
                    string getterConst = property.isGetterConst ? " const" : "";
                    if (property.hasGetter)
                    {
                        string getterLine = $"public:\n    {property.type} Get{property.name}(){getterConst};";
                        headerLinesModified.Add(getterLine);
                    }
                }
            }

            codeGenCompleted = true;

            headerLineIndex = SeekRegionEnd(headerLines, "Generated");
        }

        File.WriteAllLines(headerPath, headerLinesModified.ToList());
    }
}