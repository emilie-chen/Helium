#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Core/ManagedObject.h"
#include "Helium/AssetManagement/AssetType.h"
#include <filesystem>

heliumBegin

class Asset;

class AssetDescriptor : public ManagedObject
{
    MANAGED_CLASS(AssetDescriptor, ManagedObject, true);
public:
    AssetDescriptor() = default;
    explicit AssetDescriptor(AssetType type);
    NODISCARD AssetType GetType() const;

    void Serialize(YAML::Node& out) const override;
    void Deserialize(const YAML::Node& in) override;

protected:
    AssetType m_Type = AssetType::Invalid;
};

heliumEnd
