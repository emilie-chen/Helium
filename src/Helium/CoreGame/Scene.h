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

    MONO_CLASS_DEFINE(Scene)
public:
    Scene();
    ~Scene() override;

    static void RegisterInternalCalls();

private:
    Handle<Actor> m_RootActor;
};

heliumEnd
