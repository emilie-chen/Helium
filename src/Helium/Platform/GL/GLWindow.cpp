#include "Helium/HeliumPrecompiled.h"

#include "GLWindow.h"

#include <utility>

#include <imgui_internal.h>

heliumBegin

GLWindow::GLWindow(const String& title, const glm::ivec2& dim, WindowCloseCallback closeCallback)
    : m_WindowDimensions(dim), m_OnWindowClose(std::move(closeCallback))
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    if (PLATFORM == Platform::MacOS)
    {
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#ifdef heliumDebug
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);;
#endif // heliumDebug
    }

    m_Window = UnsafeHandle(glfwCreateWindow(dim.x, dim.y, title.c_str(), nullptr, nullptr));
    if (!m_Window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_Window.GetObject());
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }
    auto version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    spdlog::info("Version : {}", version);

    glfwSetWindowUserPointer(m_Window.GetObject(), this);
    glfwSetWindowSizeCallback(m_Window.GetObject(), [](GLFWwindow* wnd, int width, int height)
    {
        UnsafeHandle<GLWindow> wrappedWindow = UnsafeHandle(reinterpret_cast<GLWindow*>(glfwGetWindowUserPointer(wnd)));
        wrappedWindow->m_WindowDimensions = glm::ivec2(width, height);
        ivec2 frameBufferSize;
        glfwGetFramebufferSize(wnd, &frameBufferSize.x, &frameBufferSize.y);
        glViewport(0, 0, frameBufferSize.x, frameBufferSize.y);
    });


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(m_Window.GetObject(), true);
	ImGui_ImplOpenGL3_Init("#version 460");

    ivec2 frameBufferSize;
    glfwGetFramebufferSize(m_Window.GetObject(), &frameBufferSize.x, &frameBufferSize.y);
    const ImVec2 viewportPos = ImGui::GetMainViewport()->Pos;
    glViewport(viewportPos.x, viewportPos.y, frameBufferSize.x, frameBufferSize.y);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
#ifdef heliumDebug
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    //glDebugMessageCallback(MessageCallback, nullptr);
#endif // heliumDebug
}

GLWindow::~GLWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_Window.GetObject());
    glfwTerminate();
}

void GLWindow::PreUpdate(F32 dt)
{
    glfwPollEvents();
    glfwSwapInterval(0);
    if (glfwWindowShouldClose(m_Window.GetObject()))
    {
        spdlog::info("Window should close");
        if (m_OnWindowClose)
        {
            m_OnWindowClose();
        }
        else
        {
            spdlog::error("No window close callback");
            return;
        }
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

	ImGui::DockSpaceOverViewport();
}

void GLWindow::PostUpdate(F32 dt)
{
    ImGui::Render();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.3f, 0.2f, 1.0f);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if(ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

    glfwSwapBuffers(m_Window.GetObject());
}

void
GLWindow::MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
                          const void* userParam)
{
    spdlog::error("GL error: %s type = 0x%x, severity = 0x%x, message = %s\n",
             (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

void GLWindow::OnGUIUpdate(F32 dt)
{
    static Bool show_demo_window = true;
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
}

heliumEnd
