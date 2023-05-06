#include "Helium/HeliumPrecompiled.h"

#include "PrimitiveRendererBackend.h"

#include "Helium/Platform/GL/GLVertexArray.h"
#include "Helium/Platform/GL/GLVertexBuffer.h"
#include "Helium/Platform/GL/GLIndexBuffer.h"

heliumBegin

PrimitiveRendererBackend* PrimitiveRendererBackend::GetInstance()
{
    assert(s_Instance != nullptr);
    return s_Instance;
}

void PrimitiveRendererBackend::Initialize()
{
    s_Instance = new PrimitiveRendererBackend();
}

PrimitiveRendererBackend::PrimitiveRendererBackend()
{
    m_ShaderProgram = IShaderProgram::Create("Assets/Shaders/primitive.vert", "Assets/Shaders/primitive.frag");
    m_ShaderProgram->Use();
    m_VertexArray = MakeReference<GLVertexArray>();
    m_VertexArray->Bind();
    VertexBufferLayout layout;
    layout.AddElement({ GraphicsDataType::Float4, VertexBufferElementUsage::Position, false });
    layout.AddElement({ GraphicsDataType::Float4, VertexBufferElementUsage::Color, false });
    static std::array<F32, 32> quadVertices = {
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top left
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f  // bottom right
    };
    m_VertexBuffer = MakeReference<GLVertexBuffer>(quadVertices, layout);
    m_VertexBuffer->Bind();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    static std::array<U32, 6> quadIndices = {
		0, 1, 2, 2, 3, 0
	};
    m_IndexBuffer = MakeReference<GLIndexBuffer>(quadIndices);
    m_IndexBuffer->Bind();
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

void PrimitiveRendererBackend::RenderQuad(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix)
{
    m_ShaderProgram->Use();
	m_ShaderProgram->SetUniform("u_ModelMatrix", GraphicsDataType::Mat4, glm::value_ptr(modelMatrix));
    m_ShaderProgram->SetUniform("u_ViewMatrix", GraphicsDataType::Mat4, glm::value_ptr(viewMatrix));
	m_ShaderProgram->SetUniform("u_ProjectionMatrix", GraphicsDataType::Mat4, glm::value_ptr(projectionMatrix));
	m_VertexArray->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	m_VertexArray->Unbind();
}

heliumEnd
