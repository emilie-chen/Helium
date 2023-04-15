#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "ImGuiWindow.h"

heliumBegin

class ObjectViewerWindow final : public ImGuiWindow
{
    MANAGED_CLASS(ObjectViewerWindow, ImGuiWindow, false);
public:
    ObjectViewerWindow() = default;
    explicit ObjectViewerWindow(std::weak_ptr<ManagedObject> objectToView);

    void OnGUIUpdate(float deltaTime) override;

private:
    std::weak_ptr<ManagedObject> m_ObjectToView;
};

heliumEnd
