#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/CoreGame/ActorComponent.h"

heliumBegin

class Camera;

class AbstractRenderer : public ActorComponent
{
#pragma region Generated
    MANAGED_CLASS(AbstractRenderer, ActorComponent, false);
public:
#pragma endregion

public:
    virtual void DoRender(Handle<Camera> camera) { }
};

heliumEnd
