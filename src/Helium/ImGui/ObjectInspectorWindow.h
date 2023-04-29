#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "ImGuiWindow.h"

heliumBegin

class ObjectInspectorWindow final : public ImGuiWindow
{
    MANAGED_CLASS(ObjectInspectorWindow, ImGuiWindow, false);
public:
    ObjectInspectorWindow() = default;
    explicit ObjectInspectorWindow(Handle<ManagedObject> objectToView);

    void OnGUIUpdate(float deltaTime) override;

private:
    Handle<ManagedObject> m_ObjectToView;
};

heliumEnd
