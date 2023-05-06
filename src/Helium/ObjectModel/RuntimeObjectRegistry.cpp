#include "Helium/HeliumPrecompiled.h"

#include "RuntimeObjectRegistry.h"

#include "Helium/ObjectModel/ManagedObject.h"

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

Bool RuntimeObjectRegistry::IsObjectValid(Handle<ManagedObject> object) const
{
    if (object.Get() == nullptr)
    {
		return false;
	}

    const InstanceID instanceID = object.GetHandleInstanceID();

	if (instanceID == DefaultInstanceID)
    {
        return true;
    }

    if (instanceID.instance >= m_InstanceIDCounter)
    {
		return false; // invalid instance
	}

    if (m_InstanceIDInUse.find(instanceID.instance) != m_InstanceIDInUse.end())
    {
        return m_InstanceIDInUse.at(instanceID.instance) == instanceID.version;
    }

    return false;
}

void RuntimeObjectRegistry::UnregisterAndDestroyObject(Handle<ManagedObject> object)
{
    const InstanceID id = object->GetInstanceID();
    ReturnInstanceID(id);
    m_ActiveObjects.erase(object);
    delete object.Get();
}

InstanceID RuntimeObjectRegistry::GetNextInstanceID()
{
    if (m_InstanceIDPool.empty())
    {
        const InstanceID newID = InstanceID(m_InstanceIDCounter++, 0);
        m_InstanceIDInUse[newID.instance] = newID.version;
        return newID;
	}
    else
    {
		InstanceID id = m_InstanceIDPool.front();
		m_InstanceIDPool.pop_front();
        id.version++;
        m_InstanceIDInUse[id.instance] = id.version;
		return id;
	}
}

void RuntimeObjectRegistry::ReturnInstanceID(InstanceID id)
{
    if (id.instance >= m_InstanceIDCounter)
    {
        spdlog::error("Invalid instance ID: {} version {}", id.instance, id.version);
        return;
	}
    
    m_InstanceIDPool.push_back(id);
    m_InstanceIDInUse.erase(id.instance);
}

void QueueDestroyForEndOfFrame(Handle<ManagedObject> object)
{
    RuntimeObjectRegistry::GetInstance()->ObjectQueueDestroyForEndOfFrame(object);
}

Bool IsObjectValid(Handle<ManagedObject> object)
{
    return RuntimeObjectRegistry::GetInstance()->IsObjectValid(object);
}


heliumEnd

