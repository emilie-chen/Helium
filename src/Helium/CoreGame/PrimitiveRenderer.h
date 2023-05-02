#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/CoreGame/AbstractRenderer.h"
#include "Helium/CoreGame/PrimitiveType.h"

heliumBegin

class PrimitiveRenderer : public AbstractRenderer
{
#pragma region Generated
    MANAGED_CLASS(PrimitiveRenderer, AbstractRenderer, false);
public:
private:
    PrimitiveType m_Primitive;
public:
    void SetPrimitive(const PrimitiveType& value) { m_Primitive = value; }
public:
    PrimitiveType GetPrimitive() const { return m_Primitive; }
#pragma endregion

public:
    void OnRendererUpdate(F32 ts) override;
};

heliumEnd
