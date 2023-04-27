#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

heliumBegin

interface IVertexArray
{
    IVertexArray() = default;
    virtual ~IVertexArray() = default;
    DELETE_COPY_AND_MOVE(IVertexArray);

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void AddVertexBuffer(const Reference<IVertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const Reference<IIndexBuffer>& indexBuffer) = 0;
};

heliumEnd
