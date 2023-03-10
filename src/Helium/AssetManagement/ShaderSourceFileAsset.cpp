#include "Helium/HeliumPrecompiled.h"

#include "ShaderSourceFileAsset.h"
#include "Helium/Serialization/Serializer.h"
#include "ShaderSourceFileAssetDescriptor.h"
#include "Helium/Utility/File.h"

#include <utility>

heliumBegin

AssetType ShaderSourceFileAsset::GetType() const
{
    return AssetType::ShaderSourceFile;
}

ShaderSourceFileAsset::ShaderSourceFileAsset(Path path) : Asset(std::move(path))
{
    // load descriptor
    Path descriptorPath = m_Path;
    descriptorPath.replace_extension(m_Path.extension().string() + ".desc.yml");

    Bool descriptorValid = false;
    if (std::filesystem::exists(descriptorPath))
    {
        try
        {
            m_Descriptor = Serializer::Deserialize<ShaderSourceFileAssetDescriptor>(descriptorPath);
            if (m_Descriptor)
            {
                descriptorValid = true;
            }
        }
        catch (const std::exception& e)
        {
            spdlog::error("Failed to deserialize descriptor for asset '{}': {}", m_Path.string(), e.what());
        }
    }

    if (!descriptorValid)
    {
        m_Descriptor = MakeManaged<ShaderSourceFileAssetDescriptor>();
        Serializer::Serialize(m_Descriptor, descriptorPath);
    }
}

void ShaderSourceFileAsset::Load()
{
    if (m_Loaded)
    {
        return;
    }

    m_Text = ReadAllFromFileW(m_Path);
    m_Loaded = true;
}

void ShaderSourceFileAsset::Unload()
{
    m_Text.reset();
}

void ShaderSourceFileAsset::Reload()
{
    Unload();
    Load();
}

void ShaderSourceFileAsset::Save()
{
    if (!m_Loaded)
    {
        Load();
    }

    if (!m_Text)
    {
        return;
    }

    WriteAllToFileW(m_Path, *m_Text);
}

WString ShaderSourceFileAsset::GetText() const
{
    if (m_Text)
    {
        return *m_Text;
    }

    return WTEXT("");
}

heliumEnd
