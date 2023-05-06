#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Rendering/VirtualViewport.h"
#include "Helium/Platform/GL/GLFrameBuffer.h"

heliumBegin

class GLVirtualViewport : public IVirtualViewport
{
public:
	GLVirtualViewport(StringView name, ViewportRendererUpdate updater);

	void OnRendererUpdate(F32 dt) override;
	F32 GetAspectRatio() const override { return m_AspectRatio; }

private:
	String m_Name;
	Reference<GLFrameBuffer> m_FrameBuffer;
	ViewportRendererUpdate m_Updater;
	F32 m_AspectRatio = 1.0f;
};

heliumEnd
