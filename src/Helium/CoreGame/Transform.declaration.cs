using System.Runtime.CompilerServices;

namespace Helium;

[NativePath("Helium/CoreGame/Transform")]
public class Transform : ActorComponent
{
    public extern vec3 LocalTranslation { [MethodImpl(MethodImplOptions.InternalCall), Const] get; [MethodImpl(MethodImplOptions.InternalCall)] set; }
    public extern quat LocalRotation { [MethodImpl(MethodImplOptions.InternalCall), Const] get; [MethodImpl(MethodImplOptions.InternalCall)] set; }
    public extern vec3 LocalScale { [MethodImpl(MethodImplOptions.InternalCall), Const] get; [MethodImpl(MethodImplOptions.InternalCall)] set; }
    public mat4 LocalMatrix { get; }
    public extern vec3 WorldTranslation { [MethodImpl(MethodImplOptions.InternalCall), Const] get; }
    public extern quat WorldRotation { [MethodImpl(MethodImplOptions.InternalCall), Const] get; }
    public extern vec3 WorldScale { [MethodImpl(MethodImplOptions.InternalCall), Const] get; }
}
