#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/ManagedEnum.h"

heliumBegin

#pragma region Generated
enum class CameraType
{
    Perspective = 0,
    Orthographic = 1,
};

BEGIN_ENUM_REGISTRATION(CameraType)
    REGISTER_ENUM_VALUE(Perspective)
    REGISTER_ENUM_VALUE(Orthographic)
END_ENUM_REGISTRATION()
#pragma endregion

heliumEnd
