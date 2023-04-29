#include "Helium/HeliumPrecompiled.h"

#include "Helium/CoreGame/Transform.h"

#include "Helium/ObjectModel/RuntimeObjectRegistry.h"
#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/Reflection/PropertyType.h"

heliumBegin

#pragma region Generated
void Transform::RegisterMembers()
{
    UnsafeHandle<ManagedClassDescriptor> descriptor = GetClassDescriptor();
    descriptor->AddProperty(nameof(LocalTranslation), PropertyType::Vec3,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Transform>()->GetLocalTranslation();
    },
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<Transform>()->SetLocalTranslation(std::any_cast<vec3>(value));
    },
    nullptr);
    descriptor->AddProperty(nameof(LocalRotation), PropertyType::Quat,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Transform>()->GetLocalRotation();
    },
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<Transform>()->SetLocalRotation(std::any_cast<quat>(value));
    },
    nullptr);
    descriptor->AddProperty(nameof(LocalScale), PropertyType::Vec3,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Transform>()->GetLocalScale();
    },
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<Transform>()->SetLocalScale(std::any_cast<vec3>(value));
    },
    nullptr);
    descriptor->AddProperty(nameof(LocalMatrix), PropertyType::Mat4,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Transform>()->GetLocalMatrix();
    },
    std::nullopt,
    nullptr);
    descriptor->AddProperty(nameof(WorldTranslation), PropertyType::Vec3,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Transform>()->GetWorldTranslation();
    },
    std::nullopt,
    nullptr);
    descriptor->AddProperty(nameof(WorldRotation), PropertyType::Quat,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Transform>()->GetWorldRotation();
    },
    std::nullopt,
    nullptr);
    descriptor->AddProperty(nameof(WorldScale), PropertyType::Vec3,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Transform>()->GetWorldScale();
    },
    std::nullopt,
    nullptr);
}
#pragma endregion

void Transform::UpdateLocalMatrix()
{
    auto mat = glm::identity<glm::mat4>();
    mat = glm::scale(mat, m_LocalScale);
    mat = glm::mat4_cast(m_LocalRotation) * mat;
    mat = glm::translate(mat, m_LocalTranslation);
    m_LocalMatrix = mat;
    m_LocalMatrixIsDirty = false;
}

void Transform::SetLocalTranslation(const vec3& value)
{
    m_LocalTranslation = value;
	m_LocalMatrixIsDirty = true;
}

vec3 Transform::GetLocalTranslation() const
{
    return m_LocalTranslation;
}

void Transform::SetLocalRotation(const quat& value)
{
    m_LocalRotation = value;
	m_LocalMatrixIsDirty = true;
}

quat Transform::GetLocalRotation() const
{
   return m_LocalRotation;
}

void Transform::SetLocalScale(const vec3& value)
{
    m_LocalScale = value;
	m_LocalMatrixIsDirty = true;
}

vec3 Transform::GetLocalScale() const
{
    return m_LocalScale;
}

glm::mat4 Transform::GetLocalMatrix()
{
    if (m_LocalMatrixIsDirty)
    {
        UpdateLocalMatrix();
    }
    return m_LocalMatrix;
}

vec3 Transform::GetWorldTranslation() const
{
    return vec3();
}

quat Transform::GetWorldRotation() const
{
    return quat();
}

vec3 Transform::GetWorldScale() const
{
    return vec3();
}

heliumEnd

