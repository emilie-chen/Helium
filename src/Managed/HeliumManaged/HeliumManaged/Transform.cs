using System.Runtime.CompilerServices;
using GlmSharp;

namespace Helium;

[NativelyMapped("src/Helium/CoreGame/Transform.h")]
public class Transform : ActorComponent
{
    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern Transform();

    public vec3 localTranslation
    {
        get
        {
            _GetLocalTranslation(out vec3 result);
            return result;
        }
        set { _SetLocalTranslation(in value); }
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _GetLocalTranslation(out vec3 result);
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _SetLocalTranslation(in vec3 value);
    
    public quat localRotation
    {
        get
        {
            _GetLocalRotation(out quat result);
            return result;
        }
        set { _SetLocalRotation(in value); }
    }
    
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _GetLocalRotation(out quat result);
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _SetLocalRotation(in quat value);
    
    public vec3 localScale
    {
        get
        {
            _GetLocalScale(out vec3 result);
            return result;
        }
        set { _SetLocalScale(in value); }
    }
    
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _GetLocalScale(out vec3 result);
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _SetLocalScale(in vec3 value);
    
}
