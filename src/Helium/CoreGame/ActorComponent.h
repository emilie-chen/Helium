#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/ObjectModel/Handle.h"

heliumBegin

class Actor;

class ActorComponent : public ManagedObject
{
    MANAGED_CLASS(ActorComponent, ManagedObject, false);
public:
    Handle<Actor> GetOwnerActor() { return m_OwnerActor; }

private:
    Handle<Actor> m_OwnerActor{nullptr};

private:
    friend class Actor;
};

heliumEnd
