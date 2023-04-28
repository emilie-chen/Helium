#pragma once

#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/HeliumPrecompiled.h"

heliumBegin


class ImGuiWindow : public ManagedObject
{
    MANAGED_CLASS(ImGuiWindow, ManagedObject, false);
public:
    ImGuiWindow() = default;

    virtual void OnGUIUpdate(float deltaTime) = 0;

protected:
    bool m_IsOpen = true;
};

heliumEnd
