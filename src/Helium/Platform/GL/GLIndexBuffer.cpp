#include "Helium/HeliumPrecompiled.h"

#include "GLIndexBuffer.h"

heliumBegin

GLIndexBuffer::GLIndexBuffer(const std::span<U32>& indices)
    : m_Size(indices.size()), m_Handle(0)
{
    glGenBuffers(1, &m_Handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<U32>(indices.size() * sizeof(U32)), indices.data(), GL_DYNAMIC_DRAW);
}

GLIndexBuffer::~GLIndexBuffer()
{
    glDeleteBuffers(1, &m_Handle);
}

void GLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
}

void GLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

U32 GLIndexBuffer::GetSize() const
{
    return m_Size;
}

heliumEnd
