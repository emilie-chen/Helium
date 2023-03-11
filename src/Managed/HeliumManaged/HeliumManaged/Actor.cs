using System.Runtime.CompilerServices;

namespace Helium;

[NativelyMapped("src/Helium/CoreGame/Actor.h")]
public class Actor : ManagedObject
{
    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern Actor();
}
