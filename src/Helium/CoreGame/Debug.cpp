#include "Helium/HeliumPrecompiled.h"

#include "Debug.h"

heliumBegin

void Debug::Log(MonoString* message)
{
    char* str = mono_string_to_utf8(message);
    spdlog::info("{}", str);
    mono_free(str);
}

void Debug::LogWarning(MonoString* message)
{
    char* str = mono_string_to_utf8(message);
    spdlog::warn("{}", str);
    mono_free(str);
}

void Debug::LogError(MonoString* message)
{
    char* str = mono_string_to_utf8(message);
    spdlog::error("{}", str);
    mono_free(str);
}

void Debug::Assert2(MonoBoolean condition, MonoString* message)
{
    Assert(condition, mono_string_to_utf8(message));
}

void Debug::BuiltinTrap()
{
#if PLATFORM == Platform::Windows
    __debugbreak();
#else
    __builtin_trap();
#endif
}

void Debug::RegisterInternalCalls()
{
    mono_add_internal_call("Helium.Debug::Log", (void*)&Debug::Log);
    mono_add_internal_call("Helium.Debug::LogWarning", (void*)&Debug::LogWarning);
    mono_add_internal_call("Helium.Debug::LogError", (void*)&Debug::LogError);
    mono_add_internal_call("Helium.Debug::Assert", (void*)&Debug::Assert2);
    mono_add_internal_call("Helium.Debug::BuiltinTrap", (void*)&Debug::BuiltinTrap);
}

heliumEnd
