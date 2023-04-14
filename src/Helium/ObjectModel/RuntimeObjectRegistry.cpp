#include <Helium/Interop/MonoRuntime.h>
#include "Helium/HeliumPrecompiled.h"

#include "RuntimeObjectRegistry.h"

heliumBegin

RuntimeObjectRegistry* RuntimeObjectRegistry::GetInstance()
{
    static RuntimeObjectRegistry instance;
    return &instance;
}

void RuntimeObjectRegistry::RegisterObject(MonoObject* monoObject, const Reference <ManagedObject>& object)
{
    m_ObjectRegistryReference.left.insert(std::make_pair(monoObject, object));
}

void RuntimeObjectRegistry::UnregisterObject(const Reference<ManagedObject>& object)
{
    InitializeMonoCache();
    MonoObject* monoObject = m_ObjectRegistryReference.right.at(object);
    m_ObjectRegistryReference.right.erase(object);

    mono_field_set_value(monoObject, m_MonoCache.m_ManagedObjectNativeHandleField, nullptr);
}

void RuntimeObjectRegistry::UnregisterObject(MonoObject* monoObject)
{
    InitializeMonoCache();
    m_ObjectRegistryReference.left.erase(monoObject);
    mono_field_set_value(monoObject, m_MonoCache.m_ManagedObjectNativeHandleField, nullptr);
}

void RuntimeObjectRegistry::InitializeMonoCache()
{
    if (m_MonoCacheInitialized)
    {
        return;
    }

    MonoRuntime* monoRuntime = MonoRuntime::GetInstance();
    MonoAssembly* mainAssembly = monoRuntime->GetMainAssembly();
    MonoImage* mainImage = mono_assembly_get_image(mainAssembly);
    m_MonoCache.m_ManagedObjectClass = mono_class_from_name(mainImage, "Helium", "Object");
    m_MonoCache.m_ManagedObjectNativeHandleField = mono_class_get_field_from_name(m_MonoCache.m_ManagedObjectClass, "m_NativeHandle");

    m_MonoCacheInitialized = true;
}

heliumEnd

