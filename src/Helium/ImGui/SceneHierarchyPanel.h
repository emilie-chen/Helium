#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/Handle.h"
#include "Helium/ObjectModel/IUpdatable.h"
#include "Helium/ImGui/ImGuiWindow.h"

heliumBegin

class Scene;
class Actor;

class SceneHierarchyPanel final : public ImGuiWindow
{
public:
	SceneHierarchyPanel(Handle<Scene> scene);

	void OnGUIUpdate(F32 dt) override;

private:
	void RenderActorOnPanel(Handle<Actor> actor);

private:
	Handle<Scene> m_Scene;
};

heliumEnd
