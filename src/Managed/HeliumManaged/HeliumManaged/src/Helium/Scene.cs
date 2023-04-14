using System.Runtime.CompilerServices;

namespace Helium;

[NativelyMapped("src/Helium/CoreGame/Scene.h")]
public class Scene : Object
{
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern Scene();
}
