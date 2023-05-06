#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/IUpdatable.h"

heliumBegin

interface IVirtualViewport : IUpdatable
{
	virtual ~IVirtualViewport() = default;

	virtual void OnRendererUpdate(F32 dt) = 0;
	virtual F32 GetAspectRatio() const = 0;

	using ViewportRendererUpdate = std::function<void(F32)>;
};

heliumEnd
