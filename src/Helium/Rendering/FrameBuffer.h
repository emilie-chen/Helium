#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

interface IFrameBuffer
{
	virtual ~IFrameBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
	virtual void Resize(const vec2& viewportSize) = 0;
	virtual U64 GetFrameBufferTexture() const = 0;
};

heliumEnd
