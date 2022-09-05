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

heliumEnd
