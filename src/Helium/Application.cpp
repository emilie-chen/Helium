#include <Helium/AssetManagement/ShaderSourceFileAsset.h>
#include "Helium/HeliumPrecompiled.h"

#include "Helium/Application.h"
#include "Helium/Rendering/ShaderProgram.h"
#include "Helium/ImGui/ObjectViewerWindow.h"
#include <Helium/Utility/Stopwatch.h>
#include <Helium/ObjectModel/RuntimeObjectRegistry.h>
#include "Helium/CoreGame/Transform.h"

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
    m_Window = NativeWindow::CreateWindow("Helium Editor", ivec2(800, 600), [this]()
    {
        m_ShouldClose = true;
    });

    m_TestShader = ShaderProgram::Create("Assets/Shaders/test.vert", "Assets/Shaders/test.frag");
    m_TestShader->Use();

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(F32) * 4, nullptr);

    std::array<U32, 6> indices = {
        0, 1, 2, 2, 3, 0
    };
    GLuint indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    m_ShaderSourceFileAsset = MakeReference<ShaderSourceFileAsset>("Assets/Shaders/test.vert");

    AddGuiWindow(MakeReference<ObjectViewerWindow>(m_ShaderSourceFileAsset->GetAssetDescriptor()));
}

void Application::Execute()
{
    m_TimerSystem->SetFrameTime(std::chrono::milliseconds(16));
    m_TimerSystem->StartPulsing();
    float dt = 0.01f;
    Stopwatch sw;
    sw.Start();
    while (!m_ShouldClose)
    {
        sw.Reset();
        sw.Start();
        m_TimerSystem->WaitForSignal();
        Loop(dt);
        RuntimeObjectRegistry::GetInstance()->ReportFrameEnd();
        m_TimerSystem->ReportFrameEnd();
        dt = (float)(std::chrono::duration_cast<std::chrono::microseconds>(sw.GetElapsedTime()).count() / 1000000.0);
        //spdlog::info("Frame time: {} s", dt);
    }

    m_TimerSystem->OnApplicationStop();
    m_TimerSystem->ReportFrameEnd();
}

void Application::Loop(float deltaTime)
{
    m_Window->PreUpdate(deltaTime);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    m_Window->OnRendererUpdate(deltaTime);
    m_Window->OnUpdate(deltaTime);
    OnGUIUpdate(deltaTime);
    m_Window->PostUpdate(deltaTime);
}

void Application::FixedLoop(float deltaTime)
{

}

void Application::OnGUIUpdate(float deltaTime)
{
    m_Window->OnGUIUpdate(deltaTime);
    static bool showAboutWindow = false;
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Quit", "cmd+Q"))
            {
                m_ShouldClose = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About Helium Editor"))
            {
                showAboutWindow = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    if (showAboutWindow)
    {
        if (ImGui::Begin("About", &showAboutWindow, ImGuiWindowFlags_NoResize))
        {
            ImGui::Text("Helium Editor");
            ImGui::Text("Version 0.0.1");
            ImGui::Text("Author: Emilie Chen");
        }
        ImGui::End();
    }

    std::for_each(std::begin(m_GuiWindows), std::end(m_GuiWindows), [deltaTime](const Reference<ImGuiWindow>& window)
    {
        window->OnGUIUpdate(deltaTime);
    });
}

void Application::AddGuiWindow(const Reference<ImGuiWindow>& window)
{
    m_GuiWindows.push_back(window);
}

heliumEnd
