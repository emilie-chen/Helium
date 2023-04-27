using System.Runtime.CompilerServices;

namespace Helium;

[NativePath("Helium/CoreGame/Transform")]
public class Transform : ActorComponent
{
    public extern vec3 LocalTranslation { [MethodImpl(MethodImplOptions.InternalCall)] get; [MethodImpl(MethodImplOptions.InternalCall)] set; }
    public extern quat LocalRotation { [MethodImpl(MethodImplOptions.InternalCall)] get; [MethodImpl(MethodImplOptions.InternalCall)] set; }
    public extern vec3 LocalScale { [MethodImpl(MethodImplOptions.InternalCall)] get; [MethodImpl(MethodImplOptions.InternalCall)] set; }
}
