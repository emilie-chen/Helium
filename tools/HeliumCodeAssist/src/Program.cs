using System;
using System.Reflection;
using System.Linq;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;

namespace Helium;

#nullable enable



internal static partial class Program
{
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


    private static async Task Main(string[] args)
    {
        var q = from t in Assembly.GetExecutingAssembly().GetTypes()
                where (t.IsClass || t.IsEnum) && t.Namespace == "Helium"
                where t.IsEnum || typeof(ManagedObject).IsAssignableFrom(t)
                orderby t.Name descending
                where t.GetCustomAttribute<NativePathAttribute>() != null
                select t;
        List<Type> types = q.ToList();

        List<Task> tasks = new List<Task>();
        
        foreach (var t in types)
        {
            Task task = Task.Run(() =>
            {
                if (t.IsClass)
                {
                    ProcessManagedClass(t);
                }
                else if (t.IsEnum)
                {
                    ProcessManagedEnum(t);
                }
            });
            tasks.Add(task);
        }

        await Task.WhenAll(tasks);
    }
}
