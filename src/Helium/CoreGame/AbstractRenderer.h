#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/CoreGame/ActorComponent.h"

heliumBegin

class AbstractRenderer : public ActorComponent
{
#pragma region Generated
    MANAGED_CLASS(AbstractRenderer, ActorComponent, false);
public:
#pragma endregion

public:
    virtual void OnRendererUpdate(F32 ts) { }
};

heliumEnd
