namespace Helium;

[NativePath("Helium/Reflection/PropertyType")]
public enum PropertyType
{
    Invalid = 0,
    U8,
    U16,
    U32,
    U64,
    S8,
    S16,
    S32,
    S64,
    F32,
    F64,
    Bool,
    Char,
    String,
    Vec2,
    Vec3,
    Vec4,
    Quat,
    Mat3,
    Mat4,
    Handle,
    Enum
}
