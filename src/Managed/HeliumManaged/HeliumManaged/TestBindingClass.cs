using System.Runtime.CompilerServices;

namespace Helium;

public class TestBindingClass
{
    public static void TestManagedMethod()
    {
        Actor obj = new Actor();
        Debug.Log(obj ? "Valid" : "Invalid");
        ManagedObject.Destroy(obj);
        Debug.Log(obj ? "Valid" : "Invalid");
        
        Debug.Log("This is a log message.");
        Debug.LogWarning("This is a warning message.");
        Debug.LogError("This is an error message.");
    }
}
