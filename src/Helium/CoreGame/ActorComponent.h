#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/ObjectModel/Handle.h"
#include "Helium/ObjectModel/IUpdatable.h"

heliumBegin

class Actor;

class ActorComponent : public ManagedObject, public implements<IGameplayUpdatable>
{
    MANAGED_CLASS(ActorComponent, ManagedObject, false);
public:
    Handle<Actor> GetOwnerActor() { return m_OwnerActor; }

private:
    Handle<Actor> m_OwnerActor{nullptr};

private:
    friend class Actor;
};

template <typename T>
concept ActorComponentConcept = std::is_base_of_v<ActorComponent, T>;

heliumEnd
