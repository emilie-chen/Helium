#include "Helium/HeliumPrecompiled.h"

#include "Helium/Editor/SceneViewer.h"
#include "Helium/CoreGame/Scene.h"
#include "Helium/Platform/GL/GLVirtualViewport.h"

heliumBegin

SceneViewer::SceneViewer(Handle<Scene> scene)
    : m_Scene(scene)
{
    m_VirtualViewport = MakeReference<GLVirtualViewport>("Scene", std::bind(&SceneViewer::OnRendererUpdate, this, std::placeholders::_1));
}

SceneViewer::~SceneViewer()
{
}

void SceneViewer::OnRendererUpdate(F32 ts)
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


heliumEnd
