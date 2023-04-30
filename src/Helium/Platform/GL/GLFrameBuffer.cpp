#include "Helium/HeliumPrecompiled.h"

#include "Helium/Platform/GL/GLFrameBuffer.h"

heliumBegin

GLFrameBuffer::GLFrameBuffer(const vec2& viewportSize)
{
	glGenFramebuffers(1, &m_FrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);

	glGenTextures(1, &m_FrameBufferTexture);
	glBindTexture(GL_TEXTURE_2D, m_FrameBufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, viewportSize.x, viewportSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FrameBufferTexture, 0);
}

GLFrameBuffer::~GLFrameBuffer()
{
	glDeleteTextures(1, &m_FrameBufferTexture);
	glDeleteFramebuffers(1, &m_FrameBuffer);
}

void GLFrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
}

void GLFrameBuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLFrameBuffer::Resize(const vec2& viewportSize)
{
	Bind();
	glDeleteTextures(1, &m_FrameBufferTexture);
	m_FrameBufferTexture = 0;
	glGenTextures(1, &m_FrameBufferTexture);
	glBindTexture(GL_TEXTURE_2D, m_FrameBufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, viewportSize.x, viewportSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FrameBufferTexture, 0);
	Unbind();
}

heliumEnd
