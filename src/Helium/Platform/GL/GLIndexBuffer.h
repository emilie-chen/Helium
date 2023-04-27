#pragma once

#include "Helium/HeliumPrecompiled.h"

#include <span>

#include "Helium/Platform/GL/GL.h"
#include "Helium/Rendering/IndexBuffer.h"

heliumBegin

class GLIndexBuffer final : public implements<IIndexBuffer>
{
public:
    explicit GLIndexBuffer(const std::span<U32>& indices);
    ~GLIndexBuffer();

    DELETE_COPY_AND_MOVE(GLIndexBuffer);

    void Bind() const override;
    void Unbind() const override;

    NODISCARD U32 GetSize() const override;
private:
    GLuint m_Handle;
    U32 m_Size;
};

heliumEnd
