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
    void SetActor(Handle<Actor> actor) { m_Actor = actor; }

private:
    Handle<Actor> m_Actor;
};

heliumEnd
