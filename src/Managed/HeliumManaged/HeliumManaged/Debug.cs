using System.Runtime.CompilerServices;

namespace Helium;

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
}
