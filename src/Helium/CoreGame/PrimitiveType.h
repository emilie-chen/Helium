#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/ManagedEnum.h"

heliumBegin

#pragma region Generated
enum class PrimitiveType
{
    Cube = 0,
    Plane = 1,
};

BEGIN_ENUM_REGISTRATION(PrimitiveType)
    REGISTER_ENUM_VALUE(Cube)
    REGISTER_ENUM_VALUE(Plane)
END_ENUM_REGISTRATION()
#pragma endregion

heliumEnd
