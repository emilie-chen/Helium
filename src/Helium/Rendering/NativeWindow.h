#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/IUpdatable.h"

heliumBegin

class NativeWindow : public IUpdatable
{
public:
    using WindowCloseCallback = std::function<void()>;

    static Reference<NativeWindow> CreateWindow(const String& title, const ivec2& size, const WindowCloseCallback& closeCallback = nullptr);

    virtual ~NativeWindow() = default;
};

heliumEnd
