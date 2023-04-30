#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Rendering/FrameBuffer.h"
#include "Helium/Platform/GL/GL.h"

heliumBegin

class GLFrameBuffer : public implements<IFrameBuffer>
{
public:
	GLFrameBuffer(const vec2& viewportSize);
	~GLFrameBuffer();

	void Bind() const override;
	void Unbind() const override;
	void Resize(const vec2& viewportSize) override;
	U64 GetFrameBufferTexture() const override { return static_cast<U64>(m_FrameBufferTexture); }
	vec2 GetViewportSize() const override { return m_ViewportSize; }

private:
	vec2 m_ViewportSize;
	GLuint m_FrameBuffer;
	GLuint m_FrameBufferTexture;
};

heliumEnd

