using System.Runtime.CompilerServices;

namespace Helium;

[NativelyMapped("src/Helium/ObjectModel/ManagedObject.h")]
public class Object
{
    #pragma warning disable 649
    private nint m_NativeHandle; // will be assigned by native code
    #pragma warning restore 649
    
    public nint NativeHandle
    {
        get { return m_NativeHandle; }
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern Object();
    
    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void Destroy(Object obj);
    
    public static implicit operator bool(Object obj)
    {
        return obj.m_NativeHandle != 0;
    }
}
