#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

class ShaderProgram
{
public:
    static Reference<ShaderProgram> Create(const String& vertexShader, const String& fragmentShader);
};

heliumEnd
