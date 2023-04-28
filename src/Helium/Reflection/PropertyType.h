#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/ManagedEnum.h"

heliumBegin

#pragma region Generated
enum class PropertyType
{
    U8 = 0,
    U16 = 1,
    U32 = 2,
    U64 = 3,
    S8 = 4,
    S16 = 5,
    S32 = 6,
    S64 = 7,
    F32 = 8,
    F64 = 9,
    Bool = 10,
    Char = 11,
    String = 12,
    Vec2 = 13,
    Vec3 = 14,
    Vec4 = 15,
    Handle = 16,
};

BEGIN_ENUM_REGISTRATION(PropertyType)
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
    REGISTER_ENUM_VALUE(Handle)
END_ENUM_REGISTRATION()
#pragma endregion

heliumEnd
