#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "AssetDescriptor.h"

heliumBegin

class PlainTextFileAssetDescriptor : public AssetDescriptor
{
    MANAGED_CLASS(PlainTextFileAssetDescriptor, AssetDescriptor, true);
public:
    PlainTextFileAssetDescriptor();

    void Serialize(YAML::Node& out) const override;
    void Deserialize(const YAML::Node& in) override;
};

heliumEnd
