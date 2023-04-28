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

    void DestroyChildObjects() override;

private:
    std::vector<Handle<Actor>> m_RootActors;
};

heliumEnd
