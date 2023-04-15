#include <Helium/Interop/MonoRuntime.h>
#include "Helium/HeliumPrecompiled.h"

#include "RuntimeObjectRegistry.h"

heliumBegin

RuntimeObjectRegistry* RuntimeObjectRegistry::GetInstance()
{
    static RuntimeObjectRegistry instance;
    return &instance;
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

void RuntimeObjectRegistry::ReportFrameEnd()
{
    for (const auto& object : m_DestroyQueue)
    {
        UnregisterAndDestroyObject(object);
    }
    m_DestroyQueue.clear();
}

void RuntimeObjectRegistry::UnregisterAndDestroyObject(Handle<ManagedObject> object) const
{
    MonoObject* monoObject = object->m_ManagedInstance;
    mono_field_set_value(monoObject, m_MonoCache.m_ManagedObjectNativeHandleField, nullptr);
    delete object.Get();
}

void RuntimeObjectRegistry::ObjectQueueDestroyForEndOfFrame(MonoObject* monoObject)
{
    Handle<ManagedObject> handle = (ManagedObject*)ManagedObject::GetNativeHandle(monoObject);
    RuntimeObjectRegistry::GetInstance()->ObjectQueueDestroyForEndOfFrame(handle);
}

heliumEnd

