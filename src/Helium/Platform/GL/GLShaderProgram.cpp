#include "Helium/HeliumPrecompiled.h"

#include "GLShaderProgram.h"
#include <fstream>
#include <sstream>

heliumBegin

GLShaderProgram::GLShaderProgram(const String& vertexShaderPath, const String& fragmentShaderPath)
{
    // read files
    CompileAndLinkShadersFromSource(ReadFromFile(vertexShaderPath), ReadFromFile(fragmentShaderPath));
}

void GLShaderProgram::CompileAndLinkShadersFromSource(const String& vertSource, const String& fragSource)
{
    CompileVertexShaderFromSource(vertSource);
    CompileFragmentShaderFromSource(fragSource);
    CreateAndLinkShaderProgram();
}

void GLShaderProgram::CompileVertexShaderFromSource(const String& vert)
{
    const char* vertSource = vert.c_str();
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_VertexShader, 1, &vertSource, nullptr);
    glCompileShader(m_VertexShader);

    GLint success;
    glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(m_VertexShader, 512, nullptr, infoLog);
        spdlog::error("{}", infoLog);
        throw std::runtime_error("Failed to compile vertex shader");
    }
}

void GLShaderProgram::CompileFragmentShaderFromSource(const String& frag)
{
    const char* fragSource = frag.c_str();
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_FragmentShader, 1, &fragSource, nullptr);
    glCompileShader(m_FragmentShader);

    GLint success;
    glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(m_FragmentShader, 512, nullptr, infoLog);
        Assert(false);
        throw std::runtime_error("Failed to compile fragment shader");
    }
}

void GLShaderProgram::CreateAndLinkShaderProgram()
{
    m_Program = glCreateProgram();
    glAttachShader(m_Program, m_VertexShader);
    glAttachShader(m_Program, m_FragmentShader);
    glLinkProgram(m_Program);
    GLint success;
    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_Program, 512, nullptr, infoLog);
        spdlog::error("{}", infoLog);
        Assert(false);
        throw std::runtime_error("Failed to link shader program");
    }

    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
}

String GLShaderProgram::ReadFromFile(const String& path)
{
    std::ifstream file(path.c_str());
    if (!file.is_open())
    {
        throw_with_stacktrace<std::runtime_error>("Failed to open file: " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

GLShaderProgram::~GLShaderProgram()
{
    glDeleteProgram(m_Program);
}

void GLShaderProgram::Use() const
{
    glUseProgram(m_Program);
}
heliumEnd

