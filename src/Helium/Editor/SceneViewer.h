#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/IUpdatable.h"
#include "Helium/ObjectModel/Handle.h"

heliumBegin

class Scene;
interface IVirtualViewport;
class Camera;

class SceneViewer final : public IUpdatable
{
public:
	SceneViewer(Handle<Scene> scene);
	virtual ~SceneViewer();

	void OnRendererUpdate(F32 ts) override;

	void SetCamera(Handle<Camera> camera);

private:
	void InternalRendererUpdate(F32 ts);

private:
	Handle<Scene> m_Scene;
	Reference<IVirtualViewport> m_VirtualViewport;
	Handle<Camera> m_Camera;
};

heliumEnd
