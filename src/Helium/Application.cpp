#include "Helium/HeliumPrecompiled.h"

#include "Helium/Application.h"

#include "Helium/AssetManagement/ShaderSourceFileAsset.h"
#include "Helium/CoreGame/Actor.h"
#include "Helium/CoreGame/Camera.h"
#include "Helium/CoreGame/CameraType.h"
#include "Helium/CoreGame/Transform.h"
#include "Helium/ImGui/ObjectInspectorWindow.h"
#include "Helium/ObjectModel/EnumHandle.h"
#include "Helium/ObjectModel/RuntimeObjectRegistry.h"
#include "Helium/Platform/GL/GLIndexBuffer.h"
#include "Helium/Platform/GL/GLVertexArray.h"
#include "Helium/Platform/GL/GLVertexBuffer.h"
#include "Helium/Rendering/ShaderProgram.h"
#include "Helium/Utility/Stopwatch.h"

heliumBegin


Application::Application()
    : m_TimerSystem(MakeReference<TimerSystem>())
{
    // init
    m_Window = NativeWindow::CreateWindow("Helium Editor", ivec2(800, 600), [this]()
    {
        m_ShouldClose = true;
    });

    m_TestShader = IShaderProgram::Create("Assets/Shaders/test.vert", "Assets/Shaders/test.frag");
    m_TestShader->Use();


	std::array<F32, 4 * 8> vertices = {
	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	std::array<U32, 6> indices = {
		0, 1, 2, 2, 3, 0
	};

    Handle<Camera> camera = CreateObject<Camera>();
    Reference<ObjectInspectorWindow> cameraInspector = MakeReference<ObjectInspectorWindow>(camera);
    AddGuiWindow(cameraInspector);

    Handle<Actor> actor = CreateObject<Actor>();
    Handle<Transform> actorTransform = actor->GetComponent<Transform>();
    Reference<ObjectInspectorWindow> actorTransformInspector = MakeReference<ObjectInspectorWindow>(actorTransform);
    AddGuiWindow(actorTransformInspector);

    UnsafeHandle<ManagedClassDescriptor> transformClassDescriptor = actorTransform->GetDescriptor();

    m_VertexArray = MakeReference<GLVertexArray>();
    m_VertexArray->Bind();
    VertexBufferLayout layout;
    layout.AddElement(VertexBufferElement(
        GraphicsDataType::Float4, VertexBufferElementUsage::Position, false
    ));
    layout.AddElement(VertexBufferElement(
        GraphicsDataType::Float4, VertexBufferElementUsage::Color, false
    ));
    m_VertexBuffer = MakeReference<GLVertexBuffer>(vertices, layout);
    m_VertexBuffer->Bind();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_IndexBuffer = MakeReference<GLIndexBuffer>(indices);
    m_IndexBuffer->Bind();
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

    EnumHandle<CameraType> h = CameraType::Perspective;
    h = CameraType::Orthographic;
    h = CameraType::Perspective;
    EnumHandleRef ref = h.ToRef();
    U64 value = ref.GetValue();
    UnsafeHandle<ManagedEnumDescriptor> enumDescriptor = ref.GetDescriptor();
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
    for (int i = 0; i < 100; i++)
    {
        Handle<Actor> actor = CreateObject<Actor>();
        QueueDestroyForEndOfFrame(actor);
    }
    //QueueDestroyForEndOfFrame(actor);
    m_VertexArray->Bind();
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
            if (ImGui::MenuItem("Quit", "alt+F4"))
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
