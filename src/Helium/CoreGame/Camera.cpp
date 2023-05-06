#include "Helium/HeliumPrecompiled.h"

#include "Camera.h"
#include "Helium/Reflection/PropertyType.h"
#include "Helium/CoreGame/Transform.h"
#include "Helium/CoreGame/Actor.h"

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
    descriptor->AddProperty(nameof(ViewMatrix), PropertyType::Mat4,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Camera>()->GetViewMatrix();
    },
    std::nullopt,
    nullptr);
    descriptor->AddProperty(nameof(FOV), PropertyType::F32,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Camera>()->GetFOV();
    },
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<Camera>()->SetFOV(std::any_cast<F32>(value));
    },
    nullptr);
    descriptor->AddProperty(nameof(NearPlane), PropertyType::F32,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Camera>()->GetNearPlane();
    },
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<Camera>()->SetNearPlane(std::any_cast<F32>(value));
    },
    nullptr);
    descriptor->AddProperty(nameof(FarPlane), PropertyType::F32,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Camera>()->GetFarPlane();
    },
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<Camera>()->SetFarPlane(std::any_cast<F32>(value));
    },
    nullptr);
    descriptor->AddProperty(nameof(AspectRatio), PropertyType::F32,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Camera>()->GetAspectRatio();
    },
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<Camera>()->SetAspectRatio(std::any_cast<F32>(value));
    },
    nullptr);
}
#pragma endregion

mat4 Camera::GetProjectionMatrix()
{
    Handle<Transform> transform = GetOwnerActor()->GetComponent<Transform>();
    if (m_CameraType == CameraType::Orthographic)
    {
        // return glm::ortho(-GetOrthographicSize() * GetAspectRatio(), GetOrthographicSize() * GetAspectRatio(), -GetOrthographicSize(), GetOrthographicSize(), GetNearPlane(), GetFarPlane());
        return glm::identity<mat4>();
    }
    else
    {
        return glm::perspective(glm::radians(GetFOV()), GetAspectRatio(), GetNearPlane(), GetFarPlane());
    }
}

mat4 Camera::GetViewMatrix()
{
	Handle<Transform> transform = GetOwnerActor()->GetComponent<Transform>();
	//const vec3 position = transform->GetWorldTranslation();
	//return glm::lookAt(position, position + transform->GetForward(), transform->GetUp());
    return glm::inverse(transform->GetWorldMatrix());
}

void Camera::Update()
{
}

heliumEnd
