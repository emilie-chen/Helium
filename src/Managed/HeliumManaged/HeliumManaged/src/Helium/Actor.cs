using System.Runtime.CompilerServices;

namespace Helium;

[NativelyMapped("src/Helium/CoreGame/Actor.h")]
public class Actor : Object
{
    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern Actor();

    public T GetComponent<T>() where T : ActorComponent
    {
        return (T) GetComponent_Injected(typeof(T));
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern ActorComponent GetComponent_Injected(Type type);
}
