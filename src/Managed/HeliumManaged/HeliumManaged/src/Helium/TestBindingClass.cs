using System.Diagnostics;
using System.Globalization;
using System.Runtime.CompilerServices;
using GlmSharp;

namespace Helium;

public class TestBindingClass
{
    private static DateTime s_StartTime = DateTime.Now;
    
    public static void TestManagedMethod()
    {
        DateTime now = DateTime.Now;
        TimeSpan elapsed = now - s_StartTime;
        Debug.Log($"Time elapsed: {elapsed.TotalMilliseconds}");
        s_StartTime = now;
    }
}
