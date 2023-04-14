using System.Runtime.CompilerServices;

namespace Helium;

[NativelyMapped("src/Helium/CoreGame/Debug.h")]
public static class Debug
{
    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void Log(string format);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void LogWarning(string format);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void LogError(string format);

    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void Assert(bool condition, string message = "");
    
    [MethodImpl(MethodImplOptions.InternalCall)]
    public static extern void BuiltinTrap();
}
