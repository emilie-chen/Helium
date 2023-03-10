#include "Helium/HeliumPrecompiled.h"

#include "PlainTextFileAsset.h"
#include "Helium/Utility/File.h"
#include "Helium/Serialization/Serializer.h"

#include <utility>

heliumBegin

AssetType PlainTextFileAsset::GetType() const
{
    return AssetType::PlainTextFile;
}

PlainTextFileAsset::PlainTextFileAsset(Path path) : Asset(std::move(path))
{
    // load descriptor
    Path descriptorPath = m_Path;
    descriptorPath.replace_extension(m_Path.extension().string() + ".desc.yml");

    Bool descriptorValid = false;
    if (std::filesystem::exists(descriptorPath))
    {
        try
        {
            m_Descriptor = Serializer::Deserialize<PlainTextFileAssetDescriptor>(descriptorPath);
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
        m_Descriptor = MakeManaged<PlainTextFileAssetDescriptor>();
        Serializer::Serialize(m_Descriptor, descriptorPath);
    }
}

void PlainTextFileAsset::Load()
{
    if (m_Loaded)
    {
        return;
    }

    m_Text = ReadAllFromFileW(m_Path);
    m_Loaded = true;
}

void PlainTextFileAsset::Unload()
{
    m_Text.reset();
}

void PlainTextFileAsset::Reload()
{
    Unload();
    Load();
}

void PlainTextFileAsset::Save()
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

WString PlainTextFileAsset::GetText() const
{
    if (m_Text)
    {
        return *m_Text;
    }

    return WTEXT("");
}

void PlainTextFileAsset::SetText(WString text)
{
    m_Text = std::move(text);
}

heliumEnd
