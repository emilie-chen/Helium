#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/ObjectModel/Handle.h"
#include "Helium/CoreGame/ActorComponent.h"
#include "Helium/ObjectModel/IUpdatable.h"

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

    template <ActorComponentConcept T>
    std::vector<Handle<T>> GetComponentsOfBaseType();

private:
    std::unordered_map<CRC32, Handle<ActorComponent>> m_ComponentLookupTable;
    std::vector<Handle<ActorComponent>> m_Components;

private:
    friend class Actor;
    friend class ActorInspectorWindow;
};

class Actor : public ManagedObject, public implements<IGameplayUpdatable>
{
    MANAGED_CLASS(Actor, ManagedObject, false);
public:
    Actor();
    ~Actor() override;

    NODISCARD bool IsActive() const { return m_Active; }
    void SetActive(bool value) { m_Active = value; }

    void Awake() override;
    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void OnDestroy() override;
    void DestroyChildObjects() override;

    template <ActorComponentConcept T>
    Handle<T> GetComponent();

    template <ActorComponentConcept T>
    Handle<T> AddOrGetComponent();

    template <ActorComponentConcept T>
    std::vector<Handle<T>> GetComponentsOfBaseType();

    template <ActorComponentConcept T>
    void RemoveComponent();

    void RemoveComponentByTypeID(const CRC32 typeID);

    void AddChild(Handle<Actor> child);
    void RemoveChild(Handle<Actor> child);
    void SetParent(Handle<Actor> parent);
    Handle<Actor> GetParent() const { return m_Parent; }
    const std::vector<Handle<Actor>>& GetChildren() { return m_Children; }

    template <typename TInterface, typename TFunction, typename... Args>
    void Invoke(TFunction func, Args&&... args);
    
private:
    bool m_Active = true;

    // component array
    ActorComponentStore m_ComponentStore;

    std::vector<Handle<Actor>> m_Children;
    Handle<Actor> m_Parent;

    friend class ActorInspectorWindow;
};

template <ActorComponentConcept T>
Handle<T> Actor::AddOrGetComponent()
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

template<ActorComponentConcept T>
inline std::vector<Handle<T>> Actor::GetComponentsOfBaseType()
{
    return m_ComponentStore.GetComponentsOfBaseType<T>();
}

template <ActorComponentConcept T>
void Actor::RemoveComponent()
{
    RemoveComponentByTypeID(T::GetClassTypeID());
}

template <typename TInterface, typename TFunction, typename... Args>
inline void Actor::Invoke(TFunction func, Args&&... args)
{
    for (Handle<ActorComponent> component : m_ComponentStore.m_Components)
    {
        if (component.Is<TInterface>())
        {
            // func is virtual member function
            (component.As<TInterface>().Get()->*func)(std::forward<Args>(args)...);
		}
	}
}

template <ActorComponentConcept T>
Handle<T> Actor::GetComponent()
{
    const CRC32 targetTypeID = T::GetClassTypeID();
    return m_ComponentStore.GetComponentByTypeID(targetTypeID).As<T>();
}

template<ActorComponentConcept T>
inline std::vector<Handle<T>> ActorComponentStore::GetComponentsOfBaseType()
{
	std::vector<Handle<T>> components;
    for (Handle<ActorComponent> component : m_Components)
    {
        if (component.Is<T>())
        {
			components.emplace_back(component.As<T>());
		}
	}
	return components;
}


heliumEnd

