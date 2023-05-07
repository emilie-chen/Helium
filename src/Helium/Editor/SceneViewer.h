#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/IUpdatable.h"
#include "Helium/ObjectModel/Handle.h"
#include "Helium/ImGui/SceneHierarchyPanel.h"
#include "Helium/ImGui/ImGuiWindow.h"

heliumBegin

class Scene;
interface IVirtualViewport;
class Camera;
class SceneHierarchyPanel;

class SceneViewer final : public ImGuiWindow
{
public:
	SceneViewer(Handle<Scene> scene);
	virtual ~SceneViewer();

	void OnRendererUpdate(F32 ts) override;

	void SetCamera(Handle<Camera> camera);
	void OnGUIUpdate(F32 dt) override;

private:
	void InternalRendererUpdate(F32 ts);

private:
	Handle<Scene> m_Scene;
	Reference<IVirtualViewport> m_VirtualViewport;
	Handle<Camera> m_Camera;
	SceneHierarchyPanel m_HierarchyPanel;
};

heliumEnd
