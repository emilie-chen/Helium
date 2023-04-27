using System;

namespace Helium;

[AttributeUsage(AttributeTargets.Class | AttributeTargets.Enum)]
public class NativePathAttribute : Attribute
{
    public string path { get; set; }

    public NativePathAttribute(string path)
    {
        this.path = path;
    }
}

[AttributeUsage(AttributeTargets.Method)]
public class ConstAttribute : Attribute
{
}
