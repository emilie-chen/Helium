#include "Helium/HeliumPrecompiled.h"

#include "PrimitiveRenderer.h"
#include "Helium/Reflection/PropertyType.h"
#include "Helium/CoreGame/Camera.h"
#include "Helium/CoreGame/Transform.h"
#include "Helium/CoreGame/Actor.h"
#include "Helium/Rendering/PrimitiveRendererBackend.h"

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

void PrimitiveRenderer::DoRender(Handle<Camera> camera)
{
    if (!camera)
    {
        return;
    }
    Handle<Transform> transform = GetOwnerActor()->GetComponent<Transform>();
    const mat4 modelMatrix = transform->GetWorldMatrix();
    const mat4 viewMatrix = camera->GetViewMatrix();
    const mat4 projectionMatrix = camera->GetProjectionMatrix();
    static const std::array<float, 16> vertexBuffer;
    switch (m_Primitive)
    {
    case PrimitiveType::Plane:
    {
        PrimitiveRendererBackend::GetInstance()->RenderQuad(modelMatrix, viewMatrix, projectionMatrix);
        break;
    }
    }
}

heliumEnd
