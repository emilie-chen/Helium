#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Rendering/ShaderProgram.h"

heliumBegin

class GLShaderProgram final : public ShaderProgram
{
public:
    GLShaderProgram(const String& vertexShader, const String& fragmentShader);
};

heliumEnd
