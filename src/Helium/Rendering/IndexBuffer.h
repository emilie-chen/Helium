#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

class IndexBuffer
{
public:
    ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    NODISCARD virtual U32 GetSize() const = 0;
};

heliumEnd
