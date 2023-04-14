using System.Globalization;
using System.Runtime.CompilerServices;
using GlmSharp;

namespace Helium;

public class TestBindingClass
{
    public static void TestManagedMethod()
    {
        Transform t = new Transform();
        t.localTranslation = new vec3(1.2f, 3.6f, 5.7f);
        t.localScale = new vec3(2.3f, 4.4f, 6.5f);
        ManagedObject.Destroy(t);
    }
}
