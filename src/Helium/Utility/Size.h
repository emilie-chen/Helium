#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

template <typename T> requires std::is_enum_v<T>
struct DeduceEnumSize
{
    using Type = std::conditional_t<sizeof(T) == 1, uint8_t, std::conditional_t<sizeof(T) == 2, uint16_t, std::conditional_t<sizeof(T) == 4, uint32_t, uint64_t>>>;
    static constexpr size_t Size = sizeof(Type);
};

heliumEnd
