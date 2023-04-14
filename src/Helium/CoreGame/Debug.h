#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

class Debug final
{
public:
    static void RegisterInternalCalls();

    static void Log(MonoString* message);
    static void LogWarning(MonoString* message);
    static void LogError(MonoString* message);
    static void Assert2(MonoBoolean condition, MonoString* message);
    static void BuiltinTrap();
};

heliumEnd
