#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

class MonoRuntime final
{
public:
    MonoRuntime();
    ~MonoRuntime();

    static MonoRuntime* GetInstance();

    NODISCARD MonoAssembly* GetMainAssembly() const;

private:
    MonoDomain* m_Domain;
    MonoAssembly* m_MainAssembly;
    Bimap<String, MonoAssembly*> m_LoadedAssemblies;

    inline static MonoRuntime* s_Instance;

    friend class Application;
};

heliumEnd
