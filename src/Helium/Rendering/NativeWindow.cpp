#include "Helium/HeliumPrecompiled.h"

#include "NativeWindow.h"
#include "Helium/Platform/GL/GLWindow.h"

heliumBegin

Reference<NativeWindow> NativeWindow::CreateWindow(const String& title, const ivec2& size, const WindowCloseCallback& closeCallback)
{
    switch (GRAPHICS_API)
    {
        case GraphicsAPI::OpenGL:
        {
            return MakeReference<GLWindow>(title, size, closeCallback);
        }
        default:
        {
            Assert(false, "API inconnue");
        }
    }
}

heliumEnd