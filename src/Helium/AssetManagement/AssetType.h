#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Utility/CRC32.h"

heliumBegin

#define DECLARE_ASSET_TYPE_CRC32(assetType) assetType = CRC32_COMPUTE(#assetType)

enum class AssetType : CRC32
{
    Invalid = 0,
    DECLARE_ASSET_TYPE_CRC32(GLSLVertexShaderSourceFile),
    DECLARE_ASSET_TYPE_CRC32(GLSLFragmentShaderSourceFile),
    DECLARE_ASSET_TYPE_CRC32(PlainTextFile),
};

AssetType AssetTypeFromString(const String& assetTypeString);
String AssetTypeToString(AssetType assetType);

heliumEnd
