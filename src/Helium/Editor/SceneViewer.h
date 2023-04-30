#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/IUpdatable.h"
#include "Helium/ObjectModel/Handle.h"

heliumBegin

class Scene;
interface IVirtualViewport;

class SceneViewer final : public IUpdatable
{
public:
	SceneViewer(Handle<Scene> scene);
	virtual ~SceneViewer();

	void OnRendererUpdate(F32 ts) override;

private:
	Handle<Scene> m_Scene;
	Reference<IVirtualViewport> m_VirtualViewport;
};

heliumEnd
