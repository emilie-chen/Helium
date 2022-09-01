#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

class NativeWindow
{
public:
    using WindowCloseCallback = std::function<void()>;

    static Reference<NativeWindow> CreateWindow(const String& title, const ivec2& size, const WindowCloseCallback& closeCallback = nullptr);

    virtual ~NativeWindow() = default;

    virtual void PreUpdate(F32 dt) = 0;
    virtual void PostUpdate(F32 dt) = 0;
};

heliumEnd
