#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

interface IShaderProgram
{
    static Reference<IShaderProgram> Create(const String& vertexShaderPath, const String& fragmentShaderPath);

    virtual ~IShaderProgram() = default;

    virtual void Use() const = 0;
};

heliumEnd
