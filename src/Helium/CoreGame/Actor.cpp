#include "Helium/HeliumPrecompiled.h"

#include "Helium/CoreGame/Actor.h"
#include "Helium/ObjectModel/RuntimeObjectRegistry.h"
#include "Helium/CoreGame/Transform.h"

heliumBegin


void Actor::Awake()
{

}

void Actor::Start()
{

}

void Actor::Update()
{

}

void Actor::FixedUpdate()
{

}

void Actor::OnDestroy()
{

}

void Actor::DestroyChildObjects()
{
    base::DestroyChildObjects();
    // queue its components for destruction
    for (Handle<ActorComponent> component : m_ComponentStore.m_Components)
    {
        QueueDestroyForEndOfFrame(component);
    }
}

Actor::Actor()
{
    // immediately add a transform component, which is mandatory for all actors
    TryAddComponent<Transform>();
}

Actor::~Actor()
{

}

Handle<ActorComponent> ActorComponentStore::GetComponentByTypeID(const CRC32 typeID)
{
    if (m_ComponentLookupTable.contains(typeID))
    {
        return m_ComponentLookupTable[typeID];
    }

    return nullptr;
}

void ActorComponentStore::AddComponent(Handle<ActorComponent> component)
{
    m_Components.emplace_back(component);
    m_ComponentLookupTable[component->GetTypeID()] = component;
}

void ActorComponentStore::RemoveComponentByTypeID(const CRC32 typeID)
{
    if (m_ComponentLookupTable.contains(typeID))
    {
        Handle<ActorComponent> component = m_ComponentLookupTable[typeID];
        m_ComponentLookupTable.erase(typeID);
        m_Components.erase(std::find(m_Components.begin(), m_Components.end(), component));
    }
}

bool ActorComponentStore::HasComponentByTypeID(const CRC32 typeID)
{
    return m_ComponentLookupTable.contains(typeID);
}

heliumEnd

