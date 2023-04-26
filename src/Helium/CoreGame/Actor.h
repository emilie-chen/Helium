#pragma once

#include <Helium/ObjectModel/ManagedObject.h>
#include "Helium/HeliumPrecompiled.h"

heliumBegin

class ActorComponent;

using ActorID = size_t;

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

private:
    bool m_Active = true;
    ActorID m_ID = 0;
};

heliumEnd
