#include "Helium/HeliumPrecompiled.h"

#include "Debug.h"

heliumBegin

void Debug::Log(MonoString* message)
{
    spdlog::info("{}", mono_string_to_utf8(message));
}

void Debug::LogWarning(MonoString* message)
{
    spdlog::warn("{}", mono_string_to_utf8(message));
}

void Debug::LogError(MonoString* message)
{
    spdlog::error("{}", mono_string_to_utf8(message));
}

void Debug::Assert2(MonoBoolean condition, MonoString* message)
{
    Assert(condition, mono_string_to_utf8(message));
}

void Debug::RegisterInternalCalls()
{
    mono_add_internal_call("Helium.Debug::Log", (void*)&Debug::Log);
    mono_add_internal_call("Helium.Debug::LogWarning", (void*)&Debug::LogWarning);
    mono_add_internal_call("Helium.Debug::LogError", (void*)&Debug::LogError);
    mono_add_internal_call("Helium.Debug::Assert", (void*)&Debug::Assert2);
}

heliumEnd
