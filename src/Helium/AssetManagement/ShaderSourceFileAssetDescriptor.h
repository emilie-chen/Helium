#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "PlainTextFileAssetDescriptor.h"
#include "Helium/ObjectModel/ManagedEnum.h"

heliumBegin

enum class ShaderType
{
    Invalid = 0,
    Vertex,
    Pixel,
    Geometry,
    Hull,
    Domain,
    Compute,
};

BEGIN_ENUM_REGISTRATION(ShaderType)
    REGISTER_ENUM_VALUE(Invalid)
    REGISTER_ENUM_VALUE(Vertex)
    REGISTER_ENUM_VALUE(Pixel)
    REGISTER_ENUM_VALUE(Geometry)
    REGISTER_ENUM_VALUE(Hull)
    REGISTER_ENUM_VALUE(Domain)
    REGISTER_ENUM_VALUE(Compute)
END_ENUM_REGISTRATION()

enum class ShaderLanguage
{
    Invalid = 0,
    HLSL,
    GLSL,
};

BEGIN_ENUM_REGISTRATION(ShaderLanguage)
    REGISTER_ENUM_VALUE(Invalid)
    REGISTER_ENUM_VALUE(HLSL)
    REGISTER_ENUM_VALUE(GLSL)
END_ENUM_REGISTRATION()

class ShaderSourceFileAssetDescriptor final : public AssetDescriptor
{
    MANAGED_CLASS(ShaderSourceFileAssetDescriptor, AssetDescriptor, true);

public:
    NODISCARD ShaderType GetShaderType() const
    {
        return m_ShaderType;
    }

    void SetShaderType(ShaderType shaderType)
    {
        m_ShaderType = shaderType;
    }

    NODISCARD ShaderLanguage GetShaderLanguage() const
    {
        return m_ShaderLanguage;
    }

    void SetShaderLanguage(ShaderLanguage lang)
    {
        m_ShaderLanguage = lang;
    }

    void Serialize(YAML::Node& out) const override;
    void Deserialize(const YAML::Node& in) override;

private:
    ShaderType m_ShaderType{ShaderType::Invalid};
    ShaderLanguage m_ShaderLanguage{ShaderLanguage::Invalid};
};

heliumEnd
