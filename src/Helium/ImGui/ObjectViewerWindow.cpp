#include "Helium/HeliumPrecompiled.h"

#include "ObjectViewerWindow.h"
#include "Helium/Serialization/Serializer.h"

#include <utility>
#include <imgui.h>

heliumBegin

ObjectViewerWindow::ObjectViewerWindow(std::weak_ptr<ManagedObject> objectToView)
    : m_ObjectToView(std::move(objectToView))
{
    Assert(!m_ObjectToView.expired());
}

void ObjectViewerWindow::OnGUIUpdate(float deltaTime)
{
    if (!m_IsOpen)
    {
        return;
    }
    ImGui::Begin("Object Viewer", &m_IsOpen);
    // serialize object here
    Reference<ManagedObject> obj = m_ObjectToView.lock();
    if (obj)
    {
        String content = Serializer::Serialize(obj);
        ImGui::Text("%s", content.c_str());
        UnsafeHandle<ManagedClassDescriptor> descriptor = obj->GetDescriptor();
    }
    else
    {
        ImGui::Text("Invalid object");
    }

    ImGui::End();
}

heliumEnd


