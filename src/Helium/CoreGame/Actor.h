#pragma once

#include <Helium/ObjectModel/ManagedObject.h>
#include "Helium/HeliumPrecompiled.h"

heliumBegin

class ActorComponent;

class Actor : public ManagedObject
{
    MANAGED_CLASS(Actor, ManagedObject, false);
public:
    Actor() = default;

    static MonoObject* ctor(MonoObject* instance);

    static void RegisterInternalCalls();

    NODISCARD bool IsActive() const { return m_Active; }
    void SetActive(bool value) { m_Active = value; }

    void Awake();
    void Start();
    void Update();
    void FixedUpdate();
    void OnDestroy();

private:
    bool m_Active = true;

private:
    static MonoObject* GetComponent_Injected(MonoObject* actorInstance, MonoReflectionType* type);
};

heliumEnd
