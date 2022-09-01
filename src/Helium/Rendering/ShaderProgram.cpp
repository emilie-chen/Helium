#include "Helium/HeliumPrecompiled.h"

#include "ShaderProgram.h"
#include "Helium/Platform/GL/GLShaderProgram.h"

heliumBegin

Reference<ShaderProgram> ShaderProgram::Create(const String& vertexShader, const String& fragmentShader)
{
    return MakeReference<GLShaderProgram>(vertexShader, fragmentShader);
}

heliumEnd