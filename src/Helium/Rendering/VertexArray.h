#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

heliumBegin

class VertexArray
{
public:
    VertexArray() = default;
    virtual ~VertexArray() = default;
    DELETE_COPY_AND_MOVE(VertexArray);

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const Reference<IndexBuffer>& indexBuffer) = 0;
};

heliumEnd
