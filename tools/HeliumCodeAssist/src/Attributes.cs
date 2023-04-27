using System;

namespace Helium;

[AttributeUsage(AttributeTargets.Class)]
public class NativePathAttribute : Attribute
{
    public string path { get; set; }

    public NativePathAttribute(string path)
    {
        this.path = path;
    }
}
