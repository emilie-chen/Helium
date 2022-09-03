#include "Helium/HeliumPrecompiled.h"
#include "Helium/AssetManagement/AssetType.h"

heliumBegin

AssetType AssetTypeFromString(const String& assetTypeString)
{
    auto value = static_cast<AssetType>(CRC32Compute(assetTypeString.c_str(), assetTypeString.size()));
    // validate value
    switch (value)
    {
        case AssetType::GLSLVertexShaderSourceFile:
        case AssetType::GLSLFragmentShaderSourceFile:
        case AssetType::PlainTextFile:
            return static_cast<AssetType>(value);
        default:
            return AssetType::Invalid;
    }
}

#define ASSET_TYPE_TO_STRING_CASE(assetType) case AssetType::assetType: return #assetType

String AssetTypeToString(AssetType assetType)
{
    switch (assetType)
    {
        ASSET_TYPE_TO_STRING_CASE(GLSLVertexShaderSourceFile);
        ASSET_TYPE_TO_STRING_CASE(GLSLFragmentShaderSourceFile);
        ASSET_TYPE_TO_STRING_CASE(PlainTextFile);
        default:
            return "Invalid";
    }
}

heliumEnd

