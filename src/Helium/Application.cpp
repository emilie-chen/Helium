#include "Helium/HeliumPrecompiled.h"

#include "Helium/Application.h"
#include "Helium/Core/Handle.h"
#include "Helium/Core/Reference.h"

heliumBegin

Application::Application()
    : m_TimerSystem(new TimerSystem())
{
    // init
    m_TimerSystem->InitializeSingleton(m_TimerSystem);
}

void Application::Execute()
{
    Loop();
}

Bool Application::Loop()
{

    return true;
}

heliumEnd
