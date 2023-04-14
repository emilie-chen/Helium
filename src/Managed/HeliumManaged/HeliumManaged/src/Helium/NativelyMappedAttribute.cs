namespace Helium;

public class NativelyMappedAttribute : Attribute
{
    public string HeaderPath { get; set; }
    
    public NativelyMappedAttribute(string headerPath)
    {
        HeaderPath = headerPath;
    }
}
