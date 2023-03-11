using System.Runtime.CompilerServices;

namespace Helium;

[NativelyMapped("src/Helium/ObjectModel/ManagedObject.h")]
public class ManagedObject
{
    private IntPtr m_NativeHandle;
    
    public IntPtr NativeHandle
    {
        get { return m_NativeHandle; }
    }
    
    public static T Instantiate<T>() where T : ManagedObject, new()
    {
        T managedObject = (T) InternalInstantiate(typeof(T));
        return managedObject;
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    private static extern object InternalInstantiate(Type type);
}
