#pragma once

#include "Helium/HeliumPrecompiled.h"

#include <sstream>
#include <fstream>
#include <codecvt>

heliumBegin

inline String ReadAllFromFile(const Path& path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

inline void WriteAllToFile(const Path& path, const String& data)
{
    std::ofstream file(path);
    file << data;
}

inline WString ReadAllFromFileW(const Path& path)
{
    std::wifstream file(path);
    std::wstringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

inline void WriteAllToFileW(const Path& path, const WString& data)
{
    std::wofstream file(path);
    file << data;
}

heliumEnd
