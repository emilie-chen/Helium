#include "Helium/HeliumPrecompiled.h"

#include "PlainTextFileAssetDescriptor.h"

heliumBegin

void PlainTextFileAssetDescriptor::Serialize(YAML::Node& out) const
{
    BEGIN_IMPLEMENT_SERIALIZE();
    END_IMPLEMENT_SERIALIZE();
}

void PlainTextFileAssetDescriptor::Deserialize(const YAML::Node& in)
{
    BEGIN_IMPLEMENT_DESERIALIZE();
    END_IMPLEMENT_DESERIALIZE();
}

PlainTextFileAssetDescriptor::PlainTextFileAssetDescriptor()
    : AssetDescriptor(AssetType::PlainTextFile)
{
}

heliumEnd