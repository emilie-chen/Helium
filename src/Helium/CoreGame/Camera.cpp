#include "Helium/HeliumPrecompiled.h"

#include "Camera.h"
#include "Helium/Reflection/PropertyType.h"

heliumBegin

#pragma region Generated
void Camera::RegisterMembers()
{
    UnsafeHandle<ManagedClassDescriptor> descriptor = GetClassDescriptor();
    descriptor->AddProperty(nameof(CameraType), PropertyType::Enum,
    [](Handle<ManagedObject> instance)
    {
    	return (U64) instance.As<Camera>()->GetCameraType();
    },
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<Camera>()->SetCameraType(static_cast<CameraType>(std::any_cast<U64>(value)));
    },
    CameraTypeHelper::GetDescriptor());
    descriptor->AddProperty(nameof(ProjectionMatrix), PropertyType::Mat4,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Camera>()->GetProjectionMatrix();
    },
    std::nullopt,
    nullptr);
}
#pragma endregion

mat4 Camera::GetProjectionMatrix()
{
	return glm::identity<mat4>();
}

void Camera::Update()
{
}

heliumEnd
