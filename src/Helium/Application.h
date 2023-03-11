#pragma once

#include <Helium/ImGui/ImGuiWindow.h>
#include "Helium/HeliumPrecompiled.h"

#include "Helium/Platform/GL/GL.h"
#include "Helium/TimerSystem.h"
#include "Helium/ObjectModel/Singleton.h"
#include "Helium/Rendering/NativeWindow.h"
#include "Helium/AssetManagement/ShaderSourceFileAsset.h"

heliumBegin

class ShaderProgram;

class Application final
{
public:
    Application();
    void Execute();
    void OnGUIUpdate(float deltaTime);
    void AddGuiWindow(const Reference<ImGuiWindow>& window);

private:
    void Loop();

private:
    Reference<TimerSystem> m_TimerSystem;
    Reference<NativeWindow> m_Window;
    Bool m_ShouldClose = false;
    Reference<ShaderProgram> m_TestShader;
    std::vector<Reference<ImGuiWindow>> m_GuiWindows;
    Reference<ShaderSourceFileAsset> m_ShaderSourceFileAsset;
};

heliumEnd
