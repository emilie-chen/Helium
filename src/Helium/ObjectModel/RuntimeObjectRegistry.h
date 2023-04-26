#pragma once

#include <Helium/CoreGame/Actor.h>
#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/Singleton.h"
#include "Helium/ObjectModel/Handle.h"


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

private:
    void UnregisterAndDestroyObject(Handle<ManagedObject> object);

    template <typename T, typename ... TArgs> requires std::is_base_of_v<ManagedObject, T>
    Handle<T> CreateAndRegisterObject(TArgs&& ... args)
    {
        Handle<T> object = new T(std::forward<TArgs>(args)...);
        Handle<ManagedObject> managedObject = object;
        m_ActiveObjects.insert(managedObject);
        return object;
    }

private:
    std::deque<Handle<ManagedObject>> m_DestroyQueue;
    std::unordered_set<Handle<ManagedObject>> m_ActiveObjects;

private:
    template<typename T, typename ... TArgs> requires std::is_base_of_v<ManagedObject, T>
    friend Handle<T> CreateObject(TArgs&& ... args);

    friend void QueueDestroyForEndOfFrame(Handle<ManagedObject> object);

    friend class ManagedObject;
    friend class Application;
};

template<typename T, typename ... TArgs> requires std::is_base_of_v<ManagedObject, T>
Handle<T> CreateObject(TArgs&& ... args)
{
    return RuntimeObjectRegistry::GetInstance()->CreateObject<T>(std::forward<TArgs>(args)...);
}


void QueueDestroyForEndOfFrame(Handle<ManagedObject> object);

heliumEnd
