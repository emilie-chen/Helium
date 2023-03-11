using System.Runtime.CompilerServices;

namespace Helium;

public class TestBindingClass
{
    public static void TestManagedMethod()
    {
        Actor obj = new Actor();
        Debug.Log(obj ? "obj is still valid" : "obj is no longer valid");
        ManagedObject.Destroy(obj);
        Debug.Log(obj ? "obj is still valid" : "obj is no longer valid");
    }
}
