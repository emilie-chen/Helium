#pragma once

#include <Helium/ImGui/ImGuiWindow.h>
#include "Helium/HeliumPrecompiled.h"

#include "Helium/Platform/GL/GL.h"
#include "Helium/TimerSystem.h"
#include "Helium/ObjectModel/Singleton.h"
#include "Helium/Rendering/NativeWindow.h"
#include "Helium/AssetManagement/ShaderSourceFileAsset.h"
#include "Helium/Rendering/VertexBuffer.h"
#include "Helium/Rendering/VertexArray.h"

heliumBegin

interface IShaderProgram;
interface IFrameBuffer;

class Application final
{
public:
    Application();
    void Execute();
    void OnGUIUpdate(float deltaTime);
    void AddGuiWindow(const Reference<ImGuiWindow>& window);

private:
    void Loop(float deltaTime);
    void FixedLoop(float deltaTime);

private:
    Reference<TimerSystem> m_TimerSystem;
    Reference<NativeWindow> m_Window;
    Bool m_ShouldClose = false;
    Reference<IShaderProgram> m_TestShader;
    std::vector<Reference<ImGuiWindow>> m_GuiWindows;
    Reference<ShaderSourceFileAsset> m_ShaderSourceFileAsset;
    Reference<IVertexArray> m_VertexArray;
    Reference<IVertexBuffer> m_VertexBuffer;
    Reference<IIndexBuffer> m_IndexBuffer;
    Reference<IFrameBuffer> m_FrameBuffer;
};

heliumEnd
