#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

class ShaderProgram
{
public:
    static Reference<ShaderProgram> Create(const String& vertexShaderPath, const String& fragmentShaderPath);

    virtual ~ShaderProgram() = default;

    virtual void Use() const = 0;
};

heliumEnd
