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

#define heliumBegin static_assert(!IsInHeliumNamespace::value); namespace Helium { inline namespace V0 {

#define heliumEnd } static_assert(IsInHeliumNamespace::value); }

heliumBegin

#define interface struct

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

template <typename T>
using Reference = std::shared_ptr<T>;

template <typename T>
using Handle = std::weak_ptr<T>;

template <typename T, typename ... Args>
inline Reference<T> MakeReference(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

enum class GraphicsAPI : U8
{
    Invalid = 0,
    OpenGL = 1,
    Vulkan = 2,
    Direct3D = 3,
    Metal = 4,
};

enum class Platform : U8
{
    Invalid = 0,
    Windows = 1,
    MacOS = 2,
    Linux = 3,
};

constexpr GraphicsAPI GRAPHICS_API = GraphicsAPI::OpenGL;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
constexpr Platform PLATFORM = Platform::Windows;
#elif defined(__APPLE__) || defined(__MACH__)
constexpr Platform PLATFORM = Platform::MacOS;
#elif defined(__linux__) || defined(__linux)
constexpr Platform PLATFORM = Platform::Linux;
#else
constexpr Platform PLATFORM = Platform::Invalid;
#error "Unsupported platform"
#endif // Platform

namespace Internal
{
template <typename... Args>
inline void LogError(Args&&... args)
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

#define DELETE_COPY_AND_MOVE(Type) \
    Type(const Type&) = delete; \
    Type(Type&&) = delete; \
    Type& operator=(const Type&) = delete; \
    Type& operator=(Type&&) = delete;

#define NODISCARD [[nodiscard]]

heliumEnd
