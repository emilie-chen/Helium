#include "Helium/HeliumPrecompiled.h"

#include "RuntimeObjectRegistry.h"

heliumBegin

RuntimeObjectRegistry* RuntimeObjectRegistry::GetInstance()
{
    static RuntimeObjectRegistry instance;
    return &instance;
}

void RuntimeObjectRegistry::ReportFrameEnd()
{
    for (const auto& object : m_DestroyQueue)
    {
        UnregisterAndDestroyObject(object);
    }
    m_DestroyQueue.clear();
}

void RuntimeObjectRegistry::UnregisterAndDestroyObject(Handle<ManagedObject> object)
{
    m_ActiveObjects.erase(object);
    delete object.Get();
}

void QueueDestroyForEndOfFrame(Handle<ManagedObject> object)
{
    RuntimeObjectRegistry::GetInstance()->ObjectQueueDestroyForEndOfFrame(object);
}

heliumEnd

