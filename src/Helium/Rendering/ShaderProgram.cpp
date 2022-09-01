#include "Helium/HeliumPrecompiled.h"

#include "ShaderProgram.h"
#include "Helium/Platform/GL/GLShaderProgram.h"

heliumBegin

Reference<ShaderProgram> ShaderProgram::Create(const String& vertexShaderPath, const String& fragmentShaderPath)
{
    return MakeReference<GLShaderProgram>(vertexShaderPath, fragmentShaderPath);
}

heliumEnd