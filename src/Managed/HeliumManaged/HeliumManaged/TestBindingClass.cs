using System.Globalization;
using System.Runtime.CompilerServices;
using GlmSharp;

namespace Helium;

public class TestBindingClass
{
    public static void TestManagedMethod()
    {
        Transform t = new Transform();
        t.localTranslation = new vec3(1.0f, 3.0f, 5.0f);
        Debug.Log("TestManagedMethod: " + t.localTranslation);
    }
}
