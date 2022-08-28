#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/TimerSystem.h"
#include "Helium/Core/Singleton.h"
#include "Helium/Core/Reference.h"

heliumBegin

class Application final
{
public:
    Application();
    void Execute();

private:
    Bool Loop();

private:
    Reference<TimerSystem> m_TimerSystem;
};

heliumEnd
