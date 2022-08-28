#pragma once

#include <chrono>
#include <cstddef>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <csignal>
#include <memory>

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

namespace Helium
{
    struct IsInHeliumNamespace : std::true_type {};
}

struct IsInHeliumNamespace : std::false_type {};

#define heliumBegin static_assert(!IsInHeliumNamespace::value); namespace Helium {

#define heliumEnd static_assert(IsInHeliumNamespace::value); \
}

heliumBegin

using namespace glm;
typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;
typedef float F32;
typedef double F64;
typedef std::string String;
typedef bool Bool;

namespace Internal
{
template <typename... Args>
void LogError(Args&&... args)
{
    spdlog::error(std::forward<Args>(args)...);
}

template <>
void LogError();

}

#define Interrupt() std::raise(SIGINT)

#ifdef heliumDebug
#define Assert(condition, ...) \
    if (!(condition))              \
    {                              \
        Internal::LogError(__VA_ARGS__); \
        Interrupt();               \
    }
#else
#define Assert(condition, ...)
#endif // heliumDebug

heliumEnd
