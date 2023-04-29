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
           << std::hex << i;
    return stream.str();
}

heliumEnd
