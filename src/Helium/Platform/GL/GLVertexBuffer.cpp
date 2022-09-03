#include "Helium/HeliumPrecompiled.h"

#include "GLVertexBuffer.h"

#include <utility>

heliumBegin

GLVertexBuffer::GLVertexBuffer(const std::span<F32>& vertices, VertexBufferLayout layout)
    : m_Handle(0), m_Layout(std::move(layout))
{
    glGenBuffers(1, &m_Handle);
    glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
    glBufferData(GL_ARRAY_BUFFER, static_cast<U32>(vertices.size_bytes()), vertices.data(), GL_DYNAMIC_DRAW);
}

GLVertexBuffer::~GLVertexBuffer()
{
    glDeleteBuffers(1, &m_Handle);
}

void GLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
}

void GLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const VertexBufferLayout& GLVertexBuffer::GetLayout() const
{
    return m_Layout;
}

heliumEnd
