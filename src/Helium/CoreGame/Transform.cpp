#include "Helium/ObjectModel/RuntimeObjectRegistry.h"
#include "Helium/HeliumPrecompiled.h"

#include "Helium/Interop/MonoRuntime.h"
#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/CoreGame/Transform.h"

heliumBegin

void Transform::RegisterInternalCalls()
{
    mono_add_internal_call("Helium.Transform::_GetLocalTranslation", (void*)&Transform::_GetLocalTranslation);
    mono_add_internal_call("Helium.Transform::_SetLocalTranslation", (void*)&Transform::_SetLocalTranslation);
    mono_add_internal_call("Helium.Transform::_GetLocalRotation", (void*)&Transform::_GetLocalRotation);
    mono_add_internal_call("Helium.Transform::_SetLocalRotation", (void*)&Transform::_SetLocalRotation);
    mono_add_internal_call("Helium.Transform::_GetLocalScale", (void*)&Transform::_GetLocalScale);
    mono_add_internal_call("Helium.Transform::_SetLocalScale", (void*)&Transform::_SetLocalScale);
    mono_add_internal_call("Helium.Transform::_GetLocalMatrix", (void*)&Transform::_GetLocalMatrix);

    LINK_MANAGED_CLASS();
}

void Transform::_GetLocalTranslation(MonoObject* instance, vec3& value)
{
    auto* nativeObj = (Transform*)GetNativeHandle(instance);
    value = nativeObj->GetLocalTranslation();
}

void Transform::_SetLocalTranslation(MonoObject* instance, const vec3& value)
{
    auto* nativeObj = (Transform*)GetNativeHandle(instance);
    nativeObj->SetLocalTranslation(value);
}

void Transform::_GetLocalRotation(MonoObject *instance, quat &value)
{
    auto* nativeObj = (Transform*)GetNativeHandle(instance);
    value = nativeObj->GetLocalRotation();
}

void Transform::_SetLocalRotation(MonoObject *instance, const quat &value)
{
    auto* nativeObj = (Transform*)GetNativeHandle(instance);
    nativeObj->SetLocalRotation(value);
}

void Transform::_GetLocalScale(MonoObject *instance, vec3 &value)
{
    auto* nativeObj = (Transform*)GetNativeHandle(instance);
    value = nativeObj->GetLocalScale();
}

void Transform::_SetLocalScale(MonoObject *instance, const vec3 &value)
{
    auto* nativeObj = (Transform*)GetNativeHandle(instance);
    nativeObj->SetLocalScale(value);
}

void Transform::UpdateLocalMatrix()
{
    auto mat = glm::identity<glm::mat4>();
    mat = glm::scale(mat, m_LocalScale);
    mat = glm::mat4_cast(m_LocalRotation) * mat;
    mat = glm::translate(mat, m_LocalTranslation);
    m_LocalMatrix = mat;
    m_IsDirty = false;
}

glm::mat4 Transform::GetLocalMatrix()
{
    if (m_IsDirty)
    {
        UpdateLocalMatrix();
    }
    return m_LocalMatrix;
}

void Transform::_GetLocalMatrix(MonoObject *instance, mat4 &value)
{
    auto* nativeObj = (Transform*)GetNativeHandle(instance);
    value = nativeObj->GetLocalMatrix();
}

heliumEnd

