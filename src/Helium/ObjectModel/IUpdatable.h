#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

interface IUpdatable
{
    virtual void OnRendererUpdate(F32 dt) {}
    virtual void OnUpdate(F32 dt) {}
    virtual void OnGUIUpdate(F32 dt) {}
    virtual void PreUpdate(F32 dt) {}
    virtual void PostUpdate(F32 dt) {}
};

interface IGameplayUpdatable
{
    virtual void Awake() {}
    virtual void Start() {}
    virtual void Update() {}
    virtual void FixedUpdate() {}
    virtual void OnDestroy() {}
};

heliumEnd
