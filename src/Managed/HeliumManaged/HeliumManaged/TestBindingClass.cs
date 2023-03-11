using System.Runtime.CompilerServices;

namespace Helium;

public class TestBindingClass
{
    public static void TestManagedMethod()
    {
        Console.WriteLine("TestBindingClass.TestMethod() called");
        TestInternalCall();
        Exception e;
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void TestInternalCall();
}
