#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/Singleton.h"
#include "Helium/ObjectModel/Handle.h"
#include "Helium/ObjectModel/ManagedObject.h"

heliumBegin

class ManagedObject;
class RuntimeObjectRegistry;

class RuntimeObjectRegistry final
{
private:
    static RuntimeObjectRegistry* GetInstance();

    template<typename T, typename ... TArgs> requires std::is_base_of_v<ManagedObject, T>
    Handle<T> CreateObject(TArgs&& ... args)
    {
        return CreateAndRegisterObject<T>(std::forward<TArgs>(args)...);
    }

    template<typename T> requires std::is_base_of_v<ManagedObject, T>
    void ObjectDestroyImmediate(Handle<T> object)
    {
        UnregisterAndDestroyObject(object);
    }

    template<typename T> requires std::is_base_of_v<ManagedObject, T>
    void ObjectQueueDestroyForEndOfFrame(Handle<T> object)
    {
        object->DestroyChildObjects();
        m_DestroyQueue.push_back(object);
    }


    void ReportFrameEnd();

    Bool IsObjectValid(Handle<ManagedObject> object) const;

private:
    void UnregisterAndDestroyObject(Handle<ManagedObject> object);

    template <typename T, typename ... TArgs> requires std::is_base_of_v<ManagedObject, T>
    Handle<T> CreateAndRegisterObject(TArgs&& ... args)
    {
        Handle<T> object = new T(std::forward<TArgs>(args)...);
        Handle<ManagedObject> managedObject = object;
        managedObject->m_InstanceID = GetNextInstanceID();
        m_ActiveObjects.insert(managedObject);
        return object;
    }

    InstanceID GetNextInstanceID();
    void ReturnInstanceID(InstanceID id);

    Handle<ManagedObject> RegisterObject(ManagedObject* object);

private:
    std::deque<Handle<ManagedObject>> m_DestroyQueue;
    std::unordered_set<Handle<ManagedObject>> m_ActiveObjects;

    std::deque<InstanceID> m_InstanceIDPool;
    std::unordered_map<U32, U32> m_InstanceIDInUse;
    U32 m_InstanceIDCounter = 0;
private:
    template<typename T, typename ... TArgs> requires std::is_base_of_v<ManagedObject, T>
    friend Handle<T> CreateObject(TArgs&& ... args);

    friend void QueueDestroyForEndOfFrame(Handle<ManagedObject> object);
    friend Bool IsObjectValid(Handle<ManagedObject> object);

    friend class ManagedObject;
    friend class Actor;
    friend class Application;
};

template<typename T, typename ... TArgs> requires std::is_base_of_v<ManagedObject, T>
Handle<T> CreateObject(TArgs&& ... args)
{
    return RuntimeObjectRegistry::GetInstance()->CreateObject<T>(std::forward<TArgs>(args)...);
}


void QueueDestroyForEndOfFrame(Handle<ManagedObject> object);
Bool IsObjectValid(Handle<ManagedObject> object);

heliumEnd
