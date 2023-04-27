#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/ObjectModel/Handle.h"
#include "Helium/CoreGame/ActorComponent.h"

heliumBegin

using ActorID = size_t;

class ActorComponentStore final
{
public:
    ActorComponentStore() = default;
    
    Handle<ActorComponent> GetComponentByTypeID(const CRC32 typeID);
    void AddComponent(Handle<ActorComponent> component);
    void RemoveComponentByTypeID(const CRC32 typeID);
    bool HasComponentByTypeID(const CRC32 typeID);

private:
    std::unordered_map<CRC32, Handle<ActorComponent>> m_ComponentLookupTable;
    std::vector<Handle<ActorComponent>> m_Components;

private:
    friend class Actor;
};

class Actor : public ManagedObject
{
    MANAGED_CLASS(Actor, ManagedObject, false);
public:
    Actor();
    ~Actor() override;

    NODISCARD bool IsActive() const { return m_Active; }
    void SetActive(bool value) { m_Active = value; }

    void Awake();
    void Start();
    void Update();
    void FixedUpdate();
    void OnDestroy();
    void DestroyChildObjects() override;

    template <typename T> requires std::is_base_of_v<ActorComponent, T>
    Handle<T> GetComponent();

    template <typename T> requires std::is_base_of_v<ActorComponent, T>
    Handle<T> TryAddComponent();
    
private:
    bool m_Active = true;
    ActorID m_ID = 0;

    // component array
    ActorComponentStore m_ComponentStore;
};

template <typename T> requires std::is_base_of_v<ActorComponent, T>
Handle<T> Actor::TryAddComponent()
{
    const CRC32 targetTypeID = T::GetClassTypeID();
    if (m_ComponentStore.HasComponentByTypeID(targetTypeID))
    {
        return m_ComponentStore.GetComponentByTypeID(targetTypeID).As<T>();
    }

    Handle<T> component = CreateObject<T>();
    component->m_OwnerActor = this;
    m_ComponentStore.AddComponent(component);
    return component;
}

template <typename T> requires std::is_base_of_v<ActorComponent, T>
Handle<T> Actor::GetComponent()
{
    const CRC32 targetTypeID = T::GetClassTypeID();
    return m_ComponentStore.GetComponentByTypeID(targetTypeID).As<T>();
}

heliumEnd
