#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

/**
 * @brief A simple stopwatch class, not thread-safe. Use ConcurrentStopwatch for multithreaded scenarios.
 */
class Stopwatch final
{
public:
    Stopwatch() = default;
    void Start();
    void Stop();
    void Reset();
    NODISCARD Duration GetElapsedTime() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StopTime;
    Bool m_IsRunning = false;
};

heliumEnd
