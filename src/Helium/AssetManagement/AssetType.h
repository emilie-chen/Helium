#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Utility/CRC32.h"
#include "Helium/ObjectModel/ManagedEnum.h"

heliumBegin

#define DECLARE_ASSET_TYPE_CRC32(assetType) assetType = CRC32_COMPUTE(#assetType)

enum class AssetType : CRC32
{
    Invalid = 0,
    DECLARE_ASSET_TYPE_CRC32(ShaderSourceFile),
    DECLARE_ASSET_TYPE_CRC32(PlainTextFile),
};

BEGIN_ENUM_REGISTRATION(AssetType)
    REGISTER_ENUM_VALUE(Invalid)
    REGISTER_ENUM_VALUE(ShaderSourceFile)
    REGISTER_ENUM_VALUE(PlainTextFile)
END_ENUM_REGISTRATION()

heliumEnd
