using System.Runtime.CompilerServices;
using JetBrains.Annotations;

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

    protected Object()
    {
    }
    
    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void Destroy(Object obj);
    
    /**
     * Nullability is not the same as validity. A null object is not valid, but a non-null object may be invalid if it has no native handle.
     */
    [ContractAnnotation("obj:null => false")]
    public static bool IsValid(Object? obj)
    {
        return obj != null && obj.m_NativeHandle != 0;
    }
    
    public static implicit operator bool(Object? obj)
    {
        return IsValid(obj);
    }
    
    public static bool operator ==(Object? lhs, Object? rhs)
    {
        bool lhsValid = IsValid(lhs);
        bool rhsValid = IsValid(rhs);

        if (lhsValid && rhsValid)
        {
            return lhs!.m_NativeHandle == rhs!.m_NativeHandle;
        }
        
        return lhsValid == rhsValid;
    }
    
    public static bool operator !=(Object? lhs, Object? rhs)
    {
        return !(lhs == rhs);
    }
    
    public override bool Equals(object? obj)
    {
        return obj is Object other && this == other;
    }
    
    public override int GetHashCode()
    {
        return m_NativeHandle.GetHashCode();
    }
    
    public static T Instantiate<T>(T prefab) where T : Object
    {
        return (T) Instantiate_Injected(prefab);
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    private static extern Object Instantiate_Injected(Object prefab);
}
