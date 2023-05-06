#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Platform/GL/GL.h"
#include "Helium/Rendering/ShaderProgram.h"

heliumBegin

class GLShaderProgram final : public implements<IShaderProgram>
{
public:
    GLShaderProgram(const String& vertexShaderPath, const String& fragmentShaderPath);
    ~GLShaderProgram() override;

    DELETE_COPY_AND_MOVE(GLShaderProgram);

   
    void SetUniform(StringView name, GraphicsDataType type, const void* data) override;

private:
    void CompileAndLinkShadersFromSource(const String& vertSource, const String& fragSource);
    void CompileVertexShaderFromSource(const String& vert);
    void CompileFragmentShaderFromSource(const String& frag);
    void CreateAndLinkShaderProgram();
    void Use() const override;

    static String ReadFromFile(const String& path);

    GLuint m_Program = 0, m_VertexShader = 0, m_FragmentShader = 0;
};

heliumEnd
