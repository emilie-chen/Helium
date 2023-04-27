#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Rendering/VertexBuffer.h"
#include "Helium/Rendering/VertexBufferLayout.h"

#include <glad/glad.h>
#include <span>

heliumBegin

class GLVertexBuffer final : public implements<IVertexBuffer>
{
public:
    GLVertexBuffer(const std::span<F32>& vertices, VertexBufferLayout layout);
    DELETE_COPY_AND_MOVE(GLVertexBuffer);
    ~GLVertexBuffer() override;
    void Bind() const override;
    void Unbind() const override;

    NODISCARD const VertexBufferLayout& GetLayout() const override;

private:
    GLuint m_Handle;
    VertexBufferLayout m_Layout;
};

heliumEnd
