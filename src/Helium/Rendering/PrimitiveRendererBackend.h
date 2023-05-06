#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Rendering/VertexArray.h"
#include "Helium/Rendering/ShaderProgram.h"
#include "Helium/Rendering/VertexBuffer.h"
#include "Helium/Rendering/IndexBuffer.h"

heliumBegin

class PrimitiveRendererBackend
{
public:
	static PrimitiveRendererBackend* GetInstance();
	static void Initialize();

private:
	inline static PrimitiveRendererBackend* s_Instance = nullptr;

public:
	PrimitiveRendererBackend();

	void RenderQuad(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix);

private:
	Reference<IShaderProgram> m_ShaderProgram;
	Reference<IVertexArray> m_VertexArray;
	Reference<IVertexBuffer> m_VertexBuffer;
	Reference<IIndexBuffer> m_IndexBuffer;
};

heliumEnd
