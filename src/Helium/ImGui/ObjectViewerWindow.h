#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "ImGuiWindow.h"

heliumBegin

class ObjectViewerWindow final : public ImGuiWindow
{
    MANAGED_CLASS(ObjectViewerWindow, ImGuiWindow, false);
public:
    ObjectViewerWindow() = default;
    explicit ObjectViewerWindow(Handle<ManagedObject> objectToView);

    void OnGUIUpdate(float deltaTime) override;

private:
    Handle<ManagedObject> m_ObjectToView;
};

heliumEnd
