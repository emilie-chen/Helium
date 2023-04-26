#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/ObjectModel/Handle.h"
#include "Helium/CoreGame/Actor.h"

heliumBegin

class Actor;

class Scene final : public ManagedObject
{
    MANAGED_CLASS(Scene, ManagedObject, false);
public:
    Scene();
    ~Scene() override;

private:
    Handle<Actor> m_RootActor;
};

heliumEnd
