#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/AssetManagement/AssetType.h"
#include "Helium/ObjectModel/ManagedObject.h"
#include <filesystem>

heliumBegin

class Asset : public ManagedObject
{
    MANAGED_CLASS(Asset, ManagedObject, true);
public:
    virtual void Load() = 0;
    virtual void Unload() = 0;
    virtual void Reload() = 0;
    virtual void Save() = 0;

    NODISCARD virtual AssetType GetType() const = 0;
    NODISCARD String GetPath() const;

protected:
    explicit Asset(Path path);
    Asset() = default;

protected:
    Path m_Path;
    Bool m_Loaded = false;
};

heliumEnd
