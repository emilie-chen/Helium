#include "Helium/HeliumPrecompiled.h"

#include "Helium/Platform/GL/GLVirtualViewport.h"

heliumBegin

GLVirtualViewport::GLVirtualViewport(StringView name, ViewportRendererUpdate updater)
	: m_Name(name), m_FrameBuffer(MakeReference<GLFrameBuffer>(vec2{100, 100})), m_Updater(updater)
{
}

void GLVirtualViewport::OnRendererUpdate(F32 dt)
{
	ImGui::Begin(m_Name.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
	ImVec2 viewportSize = ImGui::GetContentRegionAvail();
	m_FrameBuffer->Resize({viewportSize.x, viewportSize.y});
	m_AspectRatio = viewportSize.x / viewportSize.y;
	m_FrameBuffer->Bind();
	glViewport(0, 0, viewportSize.x, viewportSize.y);
	m_Updater(dt);
	ImGui::Image(
		(ImTextureID)m_FrameBuffer->GetFrameBufferTexture(),
		ImVec2(viewportSize.x, viewportSize.y),
		ImVec2(0, 1),
		ImVec2(1, 0)
	);
	m_FrameBuffer->Unbind();
	ImGui::End();
}

heliumEnd
