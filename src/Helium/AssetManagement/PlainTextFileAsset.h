#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Asset.h"
#include "PlainTextFileAssetDescriptor.h"

heliumBegin

class PlainTextFileAsset : public Asset
{
    MANAGED_CLASS(PlainTextFileAsset, Asset, true);
public:
    NODISCARD AssetType GetType() const override;

    explicit PlainTextFileAsset(Path path);
    PlainTextFileAsset() = default;

    void Load() override;
    void Unload() override;
    void Reload() override;
    void Save() override;

    NODISCARD WString GetText() const;
    void SetText(WString text);

    NODISCARD Reference<PlainTextFileAssetDescriptor> GetAssetDescriptor() const
    {
        return m_Descriptor;
    }

private:
    Reference<PlainTextFileAssetDescriptor> m_Descriptor;
    std::optional<WString> m_Text;
};

heliumEnd
