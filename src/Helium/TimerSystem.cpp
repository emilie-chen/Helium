#include "Helium/HeliumPrecompiled.h"

#include "TimerSystem.h"
#include "Helium/Utility/Stopwatch.h"

heliumBegin

TimerSystem::TimerSystem()
    : m_FrameTime(), m_PulsingThread(&TimerSystem::PulsingRoutine, this)
{
}

TimerSystem::~TimerSystem()
{
    m_IsPulsing.clear();
    m_PulsingThread.join();
}

void TimerSystem::StartPulsing()
{
    m_IsPulsing.test_and_set();
}

void TimerSystem::SetFrameTime(const std::optional<Duration>& frameTime)
{
    m_FrameTime = frameTime;
}

std::optional<Duration> TimerSystem::GetFrameTime() const
{
    return m_FrameTime;
}

void TimerSystem::Pulse()
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_ToMain = true;
    m_CondToMain.notify_one();
}

void TimerSystem::WaitForSignal()
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    while (!m_ToMain)
    {
        m_CondToMain.wait(lock);
    }
    m_ToMain = false;
}

void TimerSystem::ReportFrameEnd()
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_FromMain = true;
    m_CondFromMain.notify_one();
}

void TimerSystem::PulsingRoutine()
{
    while (!m_ShouldStop.test())
    {
        if (!m_IsPulsing.test())
        {
            std::this_thread::yield();
            continue;
        }
        Stopwatch stopwatch;
        stopwatch.Start();
        Pulse();
        {
            std::unique_lock<std::mutex> lock(m_Mutex);
            while (!m_FromMain)
            {
                m_CondFromMain.wait(lock);
            }
            m_FromMain = false;
        }
        stopwatch.Stop();
        Duration elapsedTime = stopwatch.GetElapsedTime();
        if (m_FrameTime)
        {
            Duration frameTime = *m_FrameTime;
            if (elapsedTime < frameTime)
            {
                std::this_thread::sleep_for(frameTime - elapsedTime);
            }
        }
    }
}

void TimerSystem::OnApplicationStop()
{
    m_ShouldStop.test_and_set();
}


heliumEnd

