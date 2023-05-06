#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

enum class GraphicsDataType;

interface IShaderProgram
{
    static Reference<IShaderProgram> Create(const String& vertexShaderPath, const String& fragmentShaderPath);

    virtual ~IShaderProgram() = default;

    virtual void Use() const = 0;

    virtual void SetUniform(StringView name, GraphicsDataType type, const void* data) = 0;
};

heliumEnd
