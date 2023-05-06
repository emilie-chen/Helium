#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/ObjectModel/Handle.h"
#include "Helium/CoreGame/Actor.h"
#include "Helium/ObjectModel/IUpdatable.h"

heliumBegin

class Actor;

class Scene final : public ManagedObject, public implements<IGameplayUpdatable>
{
    MANAGED_CLASS(Scene, ManagedObject, false);
public:
    Scene();
    ~Scene() override;

    void DestroyChildObjects() override;
    std::vector<Handle<Actor>>& GetRootActors() { return m_RootActors; }

    void AddRootActor(Handle<Actor> actor);

private:
    std::vector<Handle<Actor>> m_RootActors;
};

heliumEnd
