#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Rendering/VertexArray.h"

#include "Helium/Platform/GL/GL.h"

heliumBegin

class GLVertexArray final : public implements<IVertexArray>
{
public:
    GLVertexArray();
    ~GLVertexArray() override;

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(const Reference<IVertexBuffer>& vertexBuffer) override;
    void SetIndexBuffer(const Reference<IIndexBuffer>& indexBuffer) override;

private:
    GLuint m_Handle{0};
    U32 m_VertexBufferIndex{0};
    Reference<IIndexBuffer> m_IndexBuffer;
    Reference<IVertexBuffer> m_VertexBuffers;
};

inline constexpr GLenum GetGLType(const GraphicsDataType type)
{
    switch (type)
    {
        case GraphicsDataType::Float:
        case GraphicsDataType::Float2:
        case GraphicsDataType::Float3:
        case GraphicsDataType::Float4:
        case GraphicsDataType::Mat3:
        case GraphicsDataType::Mat4: return GL_FLOAT;

        case GraphicsDataType::Int:
        case GraphicsDataType::Int2:
        case GraphicsDataType::Int3:
        case GraphicsDataType::Int4: return GL_INT;

        default:
            Assert(false);
            return 0;
    }
}

heliumEnd
