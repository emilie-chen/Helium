#include "Helium/HeliumPrecompiled.h"

#include "Helium/Application.h"

heliumBegin

static String VERTEX_SHADER_SRC = R"(
    #version 410 core
    layout (location = 0) in vec4 in_pos;
    out vec4 pos;

    void main()
    {
        gl_Position = vec4(in_pos.x, in_pos.y, in_pos.z, 1.0);
        pos = gl_Position;
    }
)";

static String FRAGMENT_SHADER_SRC = R"(
    #version 410 core
    in vec4 pos;
    out vec4 out_color;

    float map(float x, float in_min, float in_max, float out_min, float out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    void main()
    {
        out_color = vec4(pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f, 1.0f);
    }
)";

Application::Application()
    : m_TimerSystem(MakeReference<TimerSystem>())
{
    // init
    m_TimerSystem->InitializeSingleton(m_TimerSystem);
    m_Window = NativeWindow::CreateWindow("Helium Application", ivec2(800, 600), [this]()
    {
        m_ShouldClose = true;
    });

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::array<const char*, 1> vertexShaderSources = {
    VERTEX_SHADER_SRC.c_str()
    };
    glShaderSource(vertexShader, 1, vertexShaderSources.begin(), nullptr);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        spdlog::error("{}", infoLog);
    }

    std::array<const char*, 1> fragmentShaderSources = {
    FRAGMENT_SHADER_SRC.c_str()
    };
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, fragmentShaderSources.begin(), nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        spdlog::error("{}", infoLog);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        spdlog::error("{}", infoLog);
    }

    glUseProgram(program);
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);;

    GLuint vertexArray = 0;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    GLuint vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    std::array<F32, 4 * 4> vertices = {
    -1.0f, -1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, 1.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.begin(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(F32) * 4, nullptr);

    std::array<U32, 6> indices = {
        0, 1, 2, 2, 3, 0
    };
    GLuint indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.begin(), GL_STATIC_DRAW);
}

void Application::Execute()
{
    while (!m_ShouldClose)
    {
        Loop();
    }
}

void Application::Loop()
{
    m_Window->PreUpdate(0.0f);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    m_Window->PostUpdate(0.0f);
}

heliumEnd
