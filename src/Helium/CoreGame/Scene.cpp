#include "Helium/HeliumPrecompiled.h"

#include "Scene.h"
#include "Helium/Interop/MonoRuntime.h"
#include "Helium/ObjectModel/RuntimeObjectRegistry.h"

heliumBegin

void Scene::RegisterInternalCalls()
{
    LINK_MANAGED_CLASS();
}

Scene::Scene()
{
    m_RootActor = CreateObject<Actor>();
}

Scene::~Scene()
{
    QueueDestroyForEndOfFrame(m_RootActor);
}

heliumEnd
