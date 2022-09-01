#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/TimerSystem.h"
#include "Helium/Core/Singleton.h"
#include "Helium/Rendering/NativeWindow.h"

heliumBegin

class ShaderProgram;

class Application final
{
public:
    Application();
    void Execute();

private:
    void Loop();

private:
    Reference<TimerSystem> m_TimerSystem;
    Reference<NativeWindow> m_Window;
    Bool m_ShouldClose;
    Reference<ShaderProgram> m_TestShader;
};

heliumEnd
