#include "Helium/HeliumPrecompiled.h"

#include "AssetDescriptor.h"

heliumBegin

AssetDescriptor::AssetDescriptor(AssetType type)
    : m_Type(type)
{
}

AssetType AssetDescriptor::GetType() const
{
    return m_Type;
}

void AssetDescriptor::Serialize(YAML::Node& out) const
{
    BEGIN_IMPLEMENT_SERIALIZE();
    SERIALIZE_ENUM(m_Type);
    END_IMPLEMENT_SERIALIZE();
}

void AssetDescriptor::Deserialize(const YAML::Node& in)
{
    BEGIN_IMPLEMENT_DESERIALIZE();
    DESERIALIZE_ENUM(m_Type);
    END_IMPLEMENT_DESERIALIZE();
}

heliumEnd