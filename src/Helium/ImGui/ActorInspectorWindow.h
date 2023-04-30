#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "ImGuiWindow.h"

heliumBegin

class Actor;

class ActorInspectorWindow final : public ImGuiWindow
{
    MANAGED_CLASS(ActorInspectorWindow, ImGuiWindow, false);
public:
    ActorInspectorWindow() = default;
    explicit ActorInspectorWindow(Handle<Actor> actor);

    void OnGUIUpdate(float deltaTime) override;

private:
    Handle<Actor> m_Actor;
};

heliumEnd
