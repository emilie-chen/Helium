#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/AssetManagement/AssetType.h"

heliumBegin

class Asset
{
public:
    virtual ~Asset() = default;
    virtual void Load() = 0;
    virtual void Unload() = 0;
    virtual void Reload() = 0;
    virtual void Save() = 0;

    NODISCARD virtual AssetType GetType() const = 0;
};

heliumEnd
