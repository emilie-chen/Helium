#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/Singleton.h"

heliumBegin

class TimerSystem final : public Singleton<TimerSystem>
{
private:
    std::chrono::high_resolution_clock::duration m_DefaultFrameTime{std::chrono::milliseconds(16)};
};

heliumEnd
