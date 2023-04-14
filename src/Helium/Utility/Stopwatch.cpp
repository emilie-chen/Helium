#include "Helium/HeliumPrecompiled.h"

#include "Stopwatch.h"

heliumBegin

Duration Stopwatch::GetElapsedTime() const
{
    if (m_IsRunning)
    {
        return Clock::now() - m_StartTime;
    }
    else
    {
        return m_StopTime - m_StartTime;
    }
}

void Stopwatch::Start()
{
    m_StartTime = Clock::now();
    m_IsRunning = true;
}

void Stopwatch::Stop()
{
    if (m_IsRunning)
    {
        m_StopTime = Clock::now();
        m_IsRunning = false;
    }
}

void Stopwatch::Reset()
{
    m_StartTime = Clock::now();
    m_StopTime = Clock::now();
    m_IsRunning = false;
}

heliumEnd

