using System.Diagnostics;
using System.Runtime.CompilerServices;
using GlmSharp;

namespace Helium;

[NativelyMapped("src/Helium/CoreGame/Transform.h")]
public class Transform : ActorComponent
{
    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern Transform();

    [DebuggerBrowsable(DebuggerBrowsableState.Never)]
    public vec3 localTranslation
    {
        get
        {
            _GetLocalTranslation(out vec3 result);
            #if DEBUG
            m_CachedLocalTranslation = result;
            #endif
            return result;
        }
        set
        {
            #if DEBUG
            m_CachedLocalTranslation = value;
            #endif
            _SetLocalTranslation(in value);
        }
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _GetLocalTranslation(out vec3 result);
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _SetLocalTranslation(in vec3 value);
    
    [DebuggerBrowsable(DebuggerBrowsableState.Never)]
    public quat localRotation
    {
        get
        {
            _GetLocalRotation(out quat result);
            #if DEBUG
            m_CachedLocalRotation = result;
            #endif
            return result;
        }
        set
        {
            #if DEBUG
            m_CachedLocalRotation = value;
            #endif
            _SetLocalRotation(in value);
        }
    }
    
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _GetLocalRotation(out quat result);
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _SetLocalRotation(in quat value);
    
    [DebuggerBrowsable(DebuggerBrowsableState.Never)]
    public vec3 localScale
    {
        get
        {
            _GetLocalScale(out vec3 result);
            #if DEBUG
            m_CachedLocalScale = result;
            #endif
            return result;
        }
        set
        {
            #if DEBUG
            m_CachedLocalScale = value;
            #endif
            _SetLocalScale(in value);
        }
    }
    
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _GetLocalScale(out vec3 result);
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _SetLocalScale(in vec3 value);
    
    [DebuggerBrowsable(DebuggerBrowsableState.Never)]
    public mat4 localMatrix
    {
        get
        {
            _GetLocalMatrix(out mat4 result);
            return result;
        }
    }
    
    [MethodImpl(MethodImplOptions.InternalCall)]
    private extern void _GetLocalMatrix(out mat4 result);
    
    // cached
    [DebuggerBrowsable(DebuggerBrowsableState.Collapsed)]
    private vec3 m_CachedLocalTranslation;
    [DebuggerBrowsable(DebuggerBrowsableState.Collapsed)]
    private quat m_CachedLocalRotation;
    [DebuggerBrowsable(DebuggerBrowsableState.Collapsed)]
    private vec3 m_CachedLocalScale;
}
