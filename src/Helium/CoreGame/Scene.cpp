#include "Helium/HeliumPrecompiled.h"

#include "Scene.h"
#include "Helium/ObjectModel/RuntimeObjectRegistry.h"

heliumBegin


Scene::Scene()
{
    
}

Scene::~Scene()
{
    
}

void Scene::DestroyChildObjects()
{
    for (Handle<Actor> actor : m_RootActors)
    {
        QueueDestroyForEndOfFrame(actor);
    }
    m_RootActors.clear();
}

void Scene::AddRootActor(Handle<Actor> actor)
{
    m_RootActors.push_back(actor);
}

heliumEnd
