using System.Runtime.CompilerServices;

namespace Helium;

[NativelyMapped("src/Helium/ObjectModel/ManagedObject.h")]
public class ManagedObject
{
    #pragma warning disable 649
    private IntPtr m_NativeHandle; // will be assigned by native code
    #pragma warning restore 649
    
    public IntPtr NativeHandle
    {
        get { return m_NativeHandle; }
    }

    public static T Instantiate<T>() where T : ManagedObject, new()
    {
        T managedObject = (T) InternalInstantiate(typeof(T).Namespace, typeof(T).Name);
        return managedObject;
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    private static extern object InternalInstantiate(string ns, string typeName);
    
    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void Destroy(ManagedObject obj);
    
    public static implicit operator bool(ManagedObject obj)
    {
        return obj.m_NativeHandle != IntPtr.Zero;
    }
}
