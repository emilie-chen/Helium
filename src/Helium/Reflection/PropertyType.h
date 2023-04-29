#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/ManagedEnum.h"

heliumBegin

#pragma region Generated
enum class PropertyType
{
    Invalid = 0,
    U8 = 1,
    U16 = 2,
    U32 = 3,
    U64 = 4,
    S8 = 5,
    S16 = 6,
    S32 = 7,
    S64 = 8,
    F32 = 9,
    F64 = 10,
    Bool = 11,
    Char = 12,
    String = 13,
    Vec2 = 14,
    Vec3 = 15,
    Vec4 = 16,
    Quat = 17,
    Mat3 = 18,
    Mat4 = 19,
    Handle = 20,
    Enum = 21,
};

BEGIN_ENUM_REGISTRATION(PropertyType)
    REGISTER_ENUM_VALUE(Invalid)
    REGISTER_ENUM_VALUE(U8)
    REGISTER_ENUM_VALUE(U16)
    REGISTER_ENUM_VALUE(U32)
    REGISTER_ENUM_VALUE(U64)
    REGISTER_ENUM_VALUE(S8)
    REGISTER_ENUM_VALUE(S16)
    REGISTER_ENUM_VALUE(S32)
    REGISTER_ENUM_VALUE(S64)
    REGISTER_ENUM_VALUE(F32)
    REGISTER_ENUM_VALUE(F64)
    REGISTER_ENUM_VALUE(Bool)
    REGISTER_ENUM_VALUE(Char)
    REGISTER_ENUM_VALUE(String)
    REGISTER_ENUM_VALUE(Vec2)
    REGISTER_ENUM_VALUE(Vec3)
    REGISTER_ENUM_VALUE(Vec4)
    REGISTER_ENUM_VALUE(Quat)
    REGISTER_ENUM_VALUE(Mat3)
    REGISTER_ENUM_VALUE(Mat4)
    REGISTER_ENUM_VALUE(Handle)
    REGISTER_ENUM_VALUE(Enum)
END_ENUM_REGISTRATION()
#pragma endregion

heliumEnd
