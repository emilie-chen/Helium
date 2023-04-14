#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

enum class PreferenceEntry
{
    ManagedDebug
};

class EnginePref final
{
public:
    EnginePref() = delete;

    static void Set(PreferenceEntry entry, std::any value);
    static std::any Get(PreferenceEntry entry);

private:
    inline static std::unordered_map<PreferenceEntry, std::any> s_Preferences;
};

heliumEnd
