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
}
#pragma endregion

heliumEnd
