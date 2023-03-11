using System.Runtime.CompilerServices;

namespace Helium;

public class TestBindingClass
{
    public static void TestManagedMethod()
    {
        Debug.Log("Log");
        Debug.LogWarning("LogWarning");
        Debug.LogError("LogError");
        Debug.Assert(true);
    }
}
