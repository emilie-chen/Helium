#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "ImGuiWindow.h"
#include "Helium/ImGui/ActorSelectedMessage.h"

heliumBegin

class Actor;

class ActorInspectorWindow final : public ImGuiWindow
{
    MANAGED_CLASS(ActorInspectorWindow, ImGuiWindow, false);
public:
    ActorInspectorWindow();
    explicit ActorInspectorWindow(Handle<Actor> actor);
    ~ActorInspectorWindow();

    void OnGUIUpdate(float deltaTime) override;
    void SetActor(Handle<Actor> actor) { m_Actor = actor; }
    void OnActorSelected(const ActorSelectedMessage& message);

private:
    Handle<Actor> m_Actor;
};

heliumEnd
