#include "Helium/HeliumPrecompiled.h"

#include "GLVertexArray.h"

heliumBegin

GLVertexArray::GLVertexArray()
{
    glCreateVertexArrays(1, &m_Handle);
}

GLVertexArray::~GLVertexArray()
{
    glDeleteVertexArrays(1, &m_Handle);
}

void GLVertexArray::Bind() const
{
    glBindVertexArray(m_Handle);
}

void GLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void GLVertexArray::AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer)
{
    Bind();
    vertexBuffer->Bind();
    const VertexBufferLayout& layout = vertexBuffer->GetLayout();
    for (const VertexBufferElement& element : layout.GetElements())
    {
        glEnableVertexAttribArray(m_VertexBufferIndex);
        glVertexAttribPointer(m_VertexBufferIndex,
                              static_cast<GLint>(GetElementComponentCount(element.Type)),
                              GetGLType(element.Type),
                              element.Normalized,
                              static_cast<GLsizei>(layout.GetStride()),
                              reinterpret_cast<const void*>(element.Offset));
        m_VertexBufferIndex++;
    }
}

void GLVertexArray::SetIndexBuffer(const Reference <IndexBuffer>& indexBuffer)
{
    Bind();
    indexBuffer->Bind();
    m_IndexBuffer = indexBuffer;
}

heliumEnd