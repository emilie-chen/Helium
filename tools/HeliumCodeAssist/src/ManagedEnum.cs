using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Remoting.Messaging;

namespace Helium;

struct EnumData
{
    public EnumData() { }

    public string name;
    public List<(string, int)> memberValuePairs = new List<(string, int)>();
}

internal static partial class Program
{
    private static EnumData ParseEnum(Type type)
    {
        EnumData data = new EnumData();
        data.name = type.Name;
        type.GetEnumNames().ToList().ForEach(name =>
        {
            data.memberValuePairs.Add((name, (int)Enum.Parse(type, name)));
        });
        return data;
    }

    private const string ENUM_HEADER_TEMPLATE = """
#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/ManagedEnum.h"

heliumBegin

#pragma region Generated
#pragma endregion

heliumEnd

""";

    private const string ENUM_SOURCE_TEMPLATE = """
#include "Helium/HeliumPrecompiled.h"

#include "$header"

heliumBegin

heliumEnd

""";

    private static void ProcessManagedEnumHeader(string headerPath, EnumData enumData)
    {
        string[] lines = File.ReadAllLines(headerPath);
        int regionStart = SeekRegionStart(lines, "Generated");
        int regionEnd = SeekRegionEnd(lines, "Generated");
        if (regionStart == -1 || regionEnd == -1)
        {
            throw new Exception($"Failed to find designated region in {headerPath}");
        }

        List<string> newLines = new List<string>();
        int lineIndex = 0;
        while (true)
        {
            if (lineIndex >= lines.Length)
            {
                break;
            }

            if (lineIndex == regionStart)
            {
                newLines.Add(lines[lineIndex]);
                newLines.Add($"enum class {enumData.name}");
                newLines.Add("{");
                foreach ((string name, int value) in enumData.memberValuePairs)
                {
                    newLines.Add($"    {name} = {value},");
                }
                newLines.Add("};");
                newLines.Add("");

                newLines.Add($"BEGIN_ENUM_REGISTRATION({enumData.name})");
                foreach ((string name, int value) in enumData.memberValuePairs)
                {
                    newLines.Add($"    REGISTER_ENUM_VALUE({name})");
                }
                newLines.Add("END_ENUM_REGISTRATION()");

                lineIndex = regionEnd;
                continue;
            }

            newLines.Add(lines[lineIndex]);

            lineIndex++;
        }

        File.WriteAllLines(headerPath, newLines);
    }

    private static void ProcessManagedEnum(Type type)
    {
        EnumData data = ParseEnum(type);
        NativePathAttribute pathAttribute = type.GetCustomAttribute<NativePathAttribute>();
        string path = $"src/{pathAttribute.path}";
        string headerPath = path + ".h";
        string sourcePath = path + ".cpp";

        if (!File.Exists(headerPath) && !File.Exists(sourcePath))
        {
            File.WriteAllText(headerPath, ENUM_HEADER_TEMPLATE);
            File.WriteAllText(sourcePath, ENUM_SOURCE_TEMPLATE.Replace("$header", Path.GetFileName(headerPath)));
        }

        ProcessManagedEnumHeader(headerPath, data);
    }
}