#include "Helium/HeliumPrecompiled.h"

#include "Helium/Editor/SceneViewer.h"
#include "Helium/CoreGame/Scene.h"
#include "Helium/Platform/GL/GLVirtualViewport.h"
#include "Helium/CoreGame/AbstractRenderer.h"

heliumBegin

SceneViewer::SceneViewer(Handle<Scene> scene)
    : m_Scene(scene)
{
    m_VirtualViewport = MakeReference<GLVirtualViewport>("Scene", std::bind(&SceneViewer::InternalRendererUpdate, this, std::placeholders::_1));
}

SceneViewer::~SceneViewer()
{
}

void SceneViewer::OnRendererUpdate(F32 ts)
{
	m_VirtualViewport->OnRendererUpdate(ts);
}

void SceneViewer::InternalRendererUpdate(F32 ts)
{
	// BFS
	std::vector<Handle<Actor>> actors = m_Scene->GetRootActors();
	std::deque<Handle<Actor>> rootActors;
	for (Handle<Actor> actor : actors)
	{
		rootActors.push_back(actor);
	}
	std::vector<Handle<AbstractRenderer>> renderers;
	while (!rootActors.empty())
	{
		Handle<Actor> actor = rootActors.front();
		rootActors.pop_front();
		if (actor->IsActive())
		{
			std::vector<Handle<AbstractRenderer>> actorRenderers = actor->GetComponentsOfBaseType<AbstractRenderer>();
			renderers.insert(renderers.end(), actorRenderers.begin(), actorRenderers.end());
			std::vector<Handle<Actor>> children = actor->GetChildren();
			for (Handle<Actor> child : children)
			{
				rootActors.push_back(child);
			}
		}
	}
	glClearColor(0.4f, 0.3f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (Handle<AbstractRenderer> renderer : renderers)
	{
		renderer->OnRendererUpdate(ts);
	}
}


heliumEnd
