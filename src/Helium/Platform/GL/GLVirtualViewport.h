#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Rendering/VirtualViewport.h"
#include "Helium/Platform/GL/GLFrameBuffer.h"

heliumBegin

class GLVirtualViewport : public IVirtualViewport
{
public:
	GLVirtualViewport(StringView name, IVirtualViewport::ViewportRendererUpdate updater);

	void OnRendererUpdate(F32 dt) override;

private:
	String m_Name;
	Reference<GLFrameBuffer> m_FrameBuffer;
	IVirtualViewport::ViewportRendererUpdate m_Updater;
};

heliumEnd
