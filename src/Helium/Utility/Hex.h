#pragma once

#include "Helium/HeliumPrecompiled.h"
#include <sstream>
#include <iomanip>

heliumBegin

template <typename T>
inline String ToHex(T i)
{
    std::stringstream stream;
    stream << "0x"
           << std::setfill('0') << std::setw(sizeof(T) * 2)
           << std::hex << i;
    return stream.str();
}

heliumEnd
