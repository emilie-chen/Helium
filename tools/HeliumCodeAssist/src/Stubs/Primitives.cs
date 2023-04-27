namespace Helium;

public struct U8 { }
public struct U16 { }
public struct U32 { }
public struct U64 { }
public struct S8 { }
public struct S16 { }
public struct S32 { }
public struct S64 { }
public struct F32 { }
public struct F64 { }
public struct Bool { }
public struct Char { }
public class String { }
public struct CRC32 { }
public struct vec2 { }
public struct vec3 { }
public struct vec4 { }
public struct mat4 { }
public struct quat { }

public class ManagedObject { }
public class Actor : ManagedObject { }
public class ActorComponent : ManagedObject { }
public struct Handle<T> where T : ManagedObject { }
public struct UnsafeHandle<T> { }
