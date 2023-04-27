using System;
using System.Reflection;
using System.Linq;
using System.Collections.Generic;
using System.IO;

namespace Helium;

#nullable enable

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
}

internal struct MethodData
{
    public MethodData()
    {
    }

    public string name;
    public string returnType;
    public List<FieldData> parameters = new List<FieldData>();
}

internal struct ManagedTypeData
{
    public ManagedTypeData()
    {
    }

    public string typeName;
    public string baseTypeName;
    public List<MethodData> methods = new List<MethodData>();
    public List<PropertyData> properties = new List<PropertyData>();
}

internal static class Program
{
    private const string HEADER_TEMPLATE = """
#pragma once

#include "Helium/HeliumPrecompiled.h"

#pragma region Includes
#pragma endregion

heliumBegin

#pragma region Forward Declarations
#pragma endregion

class $typeName : public $baseTypeName
{
#pragma region Generated
    MANAGED_CLASS($typeName, $baseTypeName, false);
#pragma endregion

#pragma region Managed Properties
#pragma endregion

};

heliumEnd

""";

    private const string SOURCE_TEMPLATE = """
#include "Helium/HeliumPrecompiled.h"

#include "$header"

#pragma region Includes
#pragma endregion

heliumBegin

#pragma region Forward Declarations
#pragma endregion

heliumEnd

""";

    private static bool IsAutoProperty(this PropertyInfo prop)
    {
        return prop.DeclaringType.GetFields(BindingFlags.NonPublic | BindingFlags.Instance)
                             .Any(f => f.Name.Contains("<" + prop.Name + ">"));
    }

    private static ManagedTypeData ParseType(Type type)
    {
        ManagedTypeData data = new ManagedTypeData();
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
                isAutoProperty = info.IsAutoProperty()
            });
        }

       
        return data;
    }

    private static (bool, string?) IsLineRegionStart(string line)
    {
        string trimmed = line.Trim();
        bool isRegionStart = trimmed.StartsWith("#pragma region");
        if (!isRegionStart)
        {
            return (false, null);
        }

        string region = trimmed.Substring("#pragma region".Length).Trim();
        return (true, region);
    }

    private static int SeekRegionStart(string[] originalLines, string region)
    {
        for (int i = 0; i < originalLines.Length; i++)
        {
            (bool isRegionStart, string? lineRegion) = IsLineRegionStart(originalLines[i]);
            if (isRegionStart && lineRegion == region)
            {
                return i;
            }
        }

        return -1;
    }

    private static int SeekRegionEnd(string[] originalLines, string region)
    {
        int regionStart = SeekRegionStart(originalLines, region);
        if (regionStart == -1)
        {
            return -1;
        }

        for (int i = regionStart + 1; i < originalLines.Length; i++)
        {
            if (originalLines[i].Contains("#pragma endregion"))
            {
                return i;
            }
        }

        return -1;
    }


    private static void Main(string[] args)
    {
        var q = from t in Assembly.GetExecutingAssembly().GetTypes()
                where t.IsClass && t.Namespace == "Helium"
                where typeof(ManagedObject).IsAssignableFrom(t)
                orderby t.Name descending
                where t.GetCustomAttribute<NativePathAttribute>() != null
                select t;
        List<Type> types = q.ToList();
        foreach (var t in types)
        {
            ManagedTypeData typeData = ParseType(t);
            NativePathAttribute pathAttribute = t.GetCustomAttribute<NativePathAttribute>();
            string path = $"src/{pathAttribute.path}";
            string headerPath = path + ".h";
            string sourcePath = path + ".cpp";
            string declarationPath = path + ".declaration.cs";
            if (!File.Exists(headerPath) && !File.Exists(sourcePath))
            {
                File.WriteAllText(headerPath, HEADER_TEMPLATE.Replace("$typeName", typeData.typeName).Replace("$baseTypeName", typeData.baseTypeName));
                File.WriteAllText(sourcePath, SOURCE_TEMPLATE.Replace("$header", Path.GetFileName(headerPath)));
            }

            List<string> headerLinesModified = new List<string>();
            string[] headerLines = File.ReadAllLines(headerPath);

            int managedPropertiesRegionStart = SeekRegionStart(headerLines, "Managed Properties");
            if (managedPropertiesRegionStart == -1)
            {
                Console.WriteLine("Managed properties not found for type " + typeData.typeName);
                continue;
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
                        if (property.hasGetter)
                        {
                            string getterLine = $"public:\n    {property.type} Get{property.name}() const;";
                            headerLinesModified.Add(getterLine);
                        }
                    }
                }

                codeGenCompleted = true;

                headerLineIndex = SeekRegionEnd(headerLines, "Managed Properties");
            }

            File.WriteAllLines(headerPath, headerLinesModified.ToList());
        }
    }
}
