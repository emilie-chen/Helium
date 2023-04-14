#include "Helium/HeliumPrecompiled.h"

#include "EnginePref.h"

#include <utility>

heliumBegin


void EnginePref::Set(PreferenceEntry entry, std::any value)
{
    s_Preferences[entry] = std::move(value);
}

std::any EnginePref::Get(PreferenceEntry entry)
{
    return s_Preferences[entry];
}

heliumEnd
