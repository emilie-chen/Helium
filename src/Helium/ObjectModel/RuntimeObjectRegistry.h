#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/Singleton.h"


heliumBegin

class ManagedObject;

class RuntimeObjectRegistry final
{
public:
    static RuntimeObjectRegistry* GetInstance();

    void RegisterObject(MonoObject* monoObject, const Reference<ManagedObject>& object);
    void UnregisterObject(const Reference<ManagedObject>& object);
    void UnregisterObject(MonoObject* monoObject);

    void InitializeMonoCache();

private:
    Bimap<MonoObject*, Reference<ManagedObject>> m_ObjectRegistryReference;
    bool m_MonoCacheInitialized = false;
    struct
    {
        MonoClass* m_ManagedObjectClass = nullptr;
        MonoClassField* m_ManagedObjectNativeHandleField = nullptr;
    } m_MonoCache;
};

heliumEnd
