#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Rendering/NativeWindow.h"
#include "Helium/Core/UnsafeHandle.h"

heliumBegin

class GLWindow final : public NativeWindow
{
public:
    GLWindow(const String& title, const ivec2& vec1, WindowCloseCallback closeCallback = nullptr);
    GLWindow(const GLWindow&) = delete;
    GLWindow(GLWindow&&) = delete;
    GLWindow& operator=(const GLWindow&) = delete;
    GLWindow& operator=(GLWindow&&) = delete;
    ~GLWindow() override;

    void PreUpdate(F32 dt) override;
    void PostUpdate(F32 dt) override;

private:
    static void GLAPIENTRY MessageCallback(GLenum source,
                                           GLenum type,
                                           GLuint id,
                                           GLenum severity,
                                           GLsizei length,
                                           const GLchar* message,
                                           const void* userParam);


private:
    UnsafeHandle<GLFWwindow> m_Window;
    WindowCloseCallback m_OnWindowClose;
    ivec2 m_WindowDimensions;
};

heliumEnd
