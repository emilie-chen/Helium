#include <Helium/AssetManagement/ShaderSourceFileAsset.h>
#include "Helium/HeliumPrecompiled.h"

#include "Helium/Application.h"
#include "Helium/Rendering/ShaderProgram.h"
#include "Helium/ImGui/ObjectViewerWindow.h"

#include <mono/metadata/exception.h>
#include <mono/metadata/debug-helpers.h>

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

    m_ShaderSourceFileAsset = MakeReference<ShaderSourceFileAsset>("Assets/Shaders/test.vert");

    AddGuiWindow(MakeReference<ObjectViewerWindow>(m_ShaderSourceFileAsset->GetAssetDescriptor()));
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
    m_Window->OnRendererUpdate(0.0f);
    m_Window->OnUpdate(0.0f);
    OnGUIUpdate(0.0f);
    m_Window->PostUpdate(0.0f);

    MonoImage* image = mono_assembly_get_image(m_MonoRuntime.m_MainAssembly);
    MonoClass* klass = mono_class_from_name(image, "Helium", "TestBindingClass");
    MonoMethod* method = mono_class_get_method_from_name(klass, "TestManagedMethod", 0);

    MonoObject* exception = nullptr;
    mono_runtime_invoke(method, nullptr, nullptr, &exception);
    if (exception)
    {
        MonoClass* exceptionClass = mono_get_exception_class();
        MonoProperty* messageProperty = mono_class_get_property_from_name(exceptionClass, "StackTrace");
        MonoMethod* messageGetter = mono_property_get_get_method(messageProperty);
        MonoString* message = (MonoString*)mono_runtime_invoke(messageGetter, exception, nullptr, nullptr);
        char* msg = mono_string_to_utf8(message);
        //spdlog::info("Exception: {}", msg);
        mono_free(msg);

        MonoException* e = mono_get_exception_runtime_wrapped(exception);
        mono_print_unhandled_exception(exception);
    }
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
