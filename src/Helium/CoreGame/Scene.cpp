#include "Helium/HeliumPrecompiled.h"

#include "Scene.h"
#include "Helium/ObjectModel/RuntimeObjectRegistry.h"

heliumBegin


Scene::Scene()
{
    m_RootActor = CreateObject<Actor>();
}

Scene::~Scene()
{
    QueueDestroyForEndOfFrame(m_RootActor);
}

heliumEnd
