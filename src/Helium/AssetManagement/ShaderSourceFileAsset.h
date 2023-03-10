#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "PlainTextFileAsset.h"
#include "ShaderSourceFileAssetDescriptor.h"

heliumBegin

class ShaderSourceFileAsset final : public Asset
{
    MANAGED_CLASS(ShaderSourceFileAsset, Asset, true);

public:
    NODISCARD AssetType GetType() const override;

    explicit ShaderSourceFileAsset(Path path);
    ShaderSourceFileAsset() = default;

    void Load() override;
    void Unload() override;
    void Reload() override;
    void Save() override;

    NODISCARD WString GetText() const;

private:
    Reference<ShaderSourceFileAssetDescriptor> m_Descriptor;
    std::optional<WString> m_Text;
};

heliumEnd
