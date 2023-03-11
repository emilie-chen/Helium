#pragma once

#include <chrono>
#include <csignal>
#include <cstddef>
#include <filesystem>
#include <functional>
#include <iostream>
#include <locale>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

#include <boost/bimap.hpp>
#include <boost/stacktrace.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <spdlog/spdlog.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace Helium
{
    struct IsInHeliumNamespace : std::true_type {};
}

struct IsInHeliumNamespace : std::false_type {};

#define heliumBegin static_assert(!IsInHeliumNamespace::value); namespace Helium { inline namespace V0 {

#define heliumEnd } static_assert(IsInHeliumNamespace::value); }

heliumBegin

#define interface struct
#define nameof(x) #x

using namespace glm;
typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;
typedef size_t Size;
typedef float F32;
typedef double F64;
typedef std::string String;
typedef std::u8string UString;
typedef std::wstring WString;
typedef std::filesystem::path Path;
typedef bool Bool;
#define TEXT(x) x
#define UTEXT(x) u8 ## x
#define WTEXT(x) L ## x

template <typename T1, typename T2>
using Bimap = boost::bimap<T1, T2>;

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
std::string format_stacktrace(const boost::stacktrace::stacktrace& trace);

template <typename... Args>
inline void LogError(Args&&... args)
{
    auto trace = boost::stacktrace::stacktrace();
    spdlog::error(std::forward<Args>(args)...);
    spdlog::error("At");
    spdlog::error("{}", format_stacktrace(trace));
}

template <>
void LogError();

}

template <typename T, typename... Args>
__attribute__((noreturn)) void throw_with_stacktrace(std::string_view message, Args&&... format)
{
    auto trace = boost::stacktrace::stacktrace();
    throw T(fmt::format(message, std::forward<Args>(format)...) + "\nAt\n" + Internal::format_stacktrace(trace));
}

template <typename T>
__attribute__((noreturn)) void throw_with_stacktrace() {
    auto trace = boost::stacktrace::stacktrace();
    throw T("At\n" + Internal::format_stacktrace(trace));
}

class AssertionError : public std::runtime_error
{
public:
    explicit AssertionError(const std::string& message = "Assertion failed")
        : std::runtime_error(message)
    {
    }
};

#define Interrupt() __builtin_trap()

#ifdef heliumDebug
#define Assert(condition, ...) \
    if (!(condition))              \
    {                              \
        Internal::LogError(__VA_ARGS__); \
        throw_with_stacktrace<AssertionError>();               \
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
