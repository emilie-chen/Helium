#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/Singleton.h"

heliumBegin

class TimerSystem final
{
public:
    TimerSystem();
    ~TimerSystem();
    void StartPulsing();
    void OnApplicationStop();
    void WaitForSignal();
    void ReportFrameEnd();
    void SetFrameTime(const std::optional<Duration>& frameTime);
    NODISCARD std::optional<Duration> GetFrameTime() const;

private:
    void Pulse();
    void PulsingRoutine();

    std::optional<Duration> m_FrameTime;

    std::condition_variable m_CondToMain, m_CondFromMain;
    volatile bool m_ToMain = false, m_FromMain = false;
    std::mutex m_Mutex;

    std::thread m_PulsingThread;

    std::atomic_flag m_IsPulsing;
    std::atomic_flag m_ShouldStop;

private:
    static constexpr Duration s_DefaultFrameTime{std::chrono::milliseconds(16)};
};

heliumEnd
