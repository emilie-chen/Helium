#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

class MonoRuntime final
{
public:
    MonoRuntime();
    ~MonoRuntime();

private:
    MonoDomain* m_Domain;
    MonoAssembly* m_MainAssembly;
    Bimap<String, MonoAssembly*> m_LoadedAssemblies;

    friend class Application;
};

heliumEnd
