#include "Helium/HeliumPrecompiled.h"

#include "ShaderSourceFileAssetDescriptor.h"

heliumBegin

void ShaderSourceFileAssetDescriptor::RegisterMembers()
{
}

void ShaderSourceFileAssetDescriptor::Serialize(YAML::Node& out) const
{
    BEGIN_IMPLEMENT_SERIALIZE();
    SERIALIZE_ENUM(m_ShaderType);
    SERIALIZE_ENUM(m_ShaderLanguage);
    END_IMPLEMENT_SERIALIZE();
}

void ShaderSourceFileAssetDescriptor::Deserialize(const YAML::Node& in)
{
    BEGIN_IMPLEMENT_DESERIALIZE();
    DESERIALIZE_ENUM(m_ShaderType);
    DESERIALIZE_ENUM(m_ShaderLanguage);
    END_IMPLEMENT_DESERIALIZE();
}

heliumEnd