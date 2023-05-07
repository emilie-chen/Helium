#include "Helium/HeliumPrecompiled.h"

#include "Helium/Application.h"

#include "Helium/AssetManagement/ShaderSourceFileAsset.h"
#include "Helium/CoreGame/Actor.h"
#include "Helium/CoreGame/Camera.h"
#include "Helium/CoreGame/CameraType.h"
#include "Helium/CoreGame/Transform.h"
#include "Helium/ImGui/ActorInspectorWindow.h"
#include "Helium/ImGui/ObjectInspector.h"
#include "Helium/ObjectModel/EnumHandle.h"
#include "Helium/ObjectModel/RuntimeObjectRegistry.h"
#include "Helium/Platform/GL/GL.h"
#include "Helium/Platform/GL/GLFrameBuffer.h"
#include "Helium/Platform/GL/GLIndexBuffer.h"
#include "Helium/Platform/GL/GLVertexArray.h"
#include "Helium/Platform/GL/GLVertexBuffer.h"
#include "Helium/Rendering/ShaderProgram.h"
#include "Helium/Utility/Stopwatch.h"
#include "Helium/CoreGame/Scene.h"
#include "Helium/ObjectModel/IUpdatable.h"
#include "Helium/CoreGame/PrimitiveRenderer.h"
#include "Helium/Rendering/PrimitiveRendererBackend.h"

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

    PrimitiveRendererBackend::Initialize();

	std::array<F32, 4 * 8> vertices = {
	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};

	std::array<U32, 6> indices = {
		0, 1, 2, 2, 3, 0
	};


    Handle<Actor> actor = CreateObject<Actor>();
    Handle<Transform> actorTransform = actor->GetComponent<Transform>();
    Reference<ActorInspectorWindow> actorInspector = MakeReference<ActorInspectorWindow>(actor);
    AddGuiWindow(actorInspector);
    Handle<Camera> camera = actor->AddOrGetComponent<Camera>();
    camera->SetCameraType(CameraType::Perspective);
    camera->SetFOV(45.0f);
    camera->SetNearPlane(0.1f);
	camera->SetFarPlane(100.0f);
	camera->SetAspectRatio(1.0f);

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

    m_FrameBuffer = MakeReference<GLFrameBuffer>(vec2{100, 100});

    m_Scene = CreateObject<Scene>();
    Reference<SceneViewer> sceneViewer = MakeReference<SceneViewer>(m_Scene);
    m_Scene->AddRootActor(actor);

    sceneViewer->SetCamera(actor->GetComponent<Camera>());
    AddGuiWindow(sceneViewer);
    m_SceneViewer = sceneViewer;

    Handle<Actor> plane = CreateObject<Actor>();
    Handle<PrimitiveRenderer> renderer = plane->AddOrGetComponent<PrimitiveRenderer>();
    renderer->SetPrimitive(PrimitiveType::Plane);
    m_Scene->AddRootActor(plane);

    m_SceneHierarchyPanel = MakeReference<SceneHierarchyPanel>(m_Scene);
    AddGuiWindow(m_SceneHierarchyPanel);
}

void Application::Execute()
{
    m_TimerSystem->SetFrameTime(std::chrono::milliseconds(16));
    m_TimerSystem->StartPulsing();
    m_Scene->Awake();
    m_Scene->Start();
    float dt = 0.01f;
    Stopwatch sw;
    sw.Start();
    while (!m_ShouldClose)
    {
        sw.Reset();
        sw.Start();
        //m_TimerSystem->WaitForSignal();
        Loop(dt);
        RuntimeObjectRegistry::GetInstance()->ReportFrameEnd();
        //m_TimerSystem->ReportFrameEnd();
        dt = (float)(std::chrono::duration_cast<std::chrono::microseconds>(sw.GetElapsedTime()).count() / 1000000.0);
        //spdlog::info("Frame time: {} s", dt);
    }

    m_TimerSystem->OnApplicationStop();
    m_TimerSystem->ReportFrameEnd();
}

void Application::Loop(float deltaTime)
{
    m_Window->PreUpdate(deltaTime);

    m_Scene->Update();
    m_SceneViewer->OnRendererUpdate(deltaTime);

    m_Window->OnRendererUpdate(deltaTime);
    m_Window->OnUpdate(deltaTime);
    OnGUIUpdate(deltaTime);
    m_SceneViewer->OnGUIUpdate(deltaTime);
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
        if (ImGui::Begin("About", &showAboutWindow))
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
