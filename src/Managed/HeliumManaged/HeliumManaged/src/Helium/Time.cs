using System.Runtime.CompilerServices;

namespace Helium;

public static class Time
{
    public static extern float deltaTime
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        get;
    }
    
    public static extern float fixedDeltaTime
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        get;
    }
}
