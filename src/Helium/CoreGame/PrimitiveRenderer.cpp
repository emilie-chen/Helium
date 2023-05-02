#include "Helium/HeliumPrecompiled.h"

#include "PrimitiveRenderer.h"
#include "Helium/Reflection/PropertyType.h"

heliumBegin

#pragma region Generated
void PrimitiveRenderer::RegisterMembers()
{
    UnsafeHandle<ManagedClassDescriptor> descriptor = GetClassDescriptor();
    descriptor->AddProperty(nameof(Primitive), PropertyType::Enum,
    [](Handle<ManagedObject> instance)
    {
    	return (U64) instance.As<PrimitiveRenderer>()->GetPrimitive();
    },
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<PrimitiveRenderer>()->SetPrimitive(static_cast<PrimitiveType>(std::any_cast<U64>(value)));
    },
    PrimitiveTypeHelper::GetDescriptor());
}
#pragma endregion

void PrimitiveRenderer::OnRendererUpdate(F32 ts)
{
}

heliumEnd
