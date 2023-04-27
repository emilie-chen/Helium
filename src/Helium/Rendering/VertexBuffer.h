#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "VertexBufferLayout.h"

heliumBegin

interface IVertexBuffer
{
public:
    virtual ~IVertexBuffer() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    NODISCARD virtual const VertexBufferLayout& GetLayout() const = 0;
};

heliumEnd
