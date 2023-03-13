#include <Helium/ObjectModel/RuntimeObjectRegistry.h>
#include "Helium/HeliumPrecompiled.h"

#include "Transform.h"

heliumBegin

void Transform::RegisterInternalCalls()
{
    mono_add_internal_call("Helium.Transform::.ctor", (void*)&Transform::ctor);
    mono_add_internal_call("Helium.Transform::_GetLocalTranslation", (void*)&Transform::_GetLocalTranslation);
    mono_add_internal_call("Helium.Transform::_SetLocalTranslation", (void*)&Transform::_SetLocalTranslation);
}

MonoObject* Transform::ctor(MonoObject* instance)
{
    Reference<Transform> nativeObj = MakeManaged<Transform>();
    ManagedObject::SetNativeHandle(instance, nativeObj.get());
    RuntimeObjectRegistry::GetInstance()->RegisterObject(instance, nativeObj);
    return instance;
}

void Transform::_GetLocalTranslation(MonoObject* instance, vec3& value)
{
    auto* nativeObj = (Transform*)GetNativeHandle(instance);
    value = nativeObj->m_LocalTranslation;
}

void Transform::_SetLocalTranslation(MonoObject* instance, const vec3& value)
{
    auto* nativeObj = (Transform*)GetNativeHandle(instance);
    nativeObj->m_LocalTranslation = value;
}


heliumEnd

