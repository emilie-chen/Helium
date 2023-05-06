#include "Helium/HeliumPrecompiled.h"

#include <glm/gtx/matrix_decompose.hpp>

#include "Helium/CoreGame/Transform.h"

#include "Helium/ObjectModel/RuntimeObjectRegistry.h"
#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/Reflection/PropertyType.h"
#include "Helium/CoreGame/Actor.h"

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
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<Transform>()->SetWorldTranslation(std::any_cast<vec3>(value));
    },
    nullptr);
    descriptor->AddProperty(nameof(WorldRotation), PropertyType::Quat,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Transform>()->GetWorldRotation();
    },
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<Transform>()->SetWorldRotation(std::any_cast<quat>(value));
    },
    nullptr);
    descriptor->AddProperty(nameof(WorldScale), PropertyType::Vec3,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Transform>()->GetWorldScale();
    },
    [](Handle<ManagedObject> instance, std::any value)
    {
    	instance.As<Transform>()->SetWorldScale(std::any_cast<vec3>(value));
    },
    nullptr);
    descriptor->AddProperty(nameof(WorldMatrix), PropertyType::Mat4,
    [](Handle<ManagedObject> instance)
    {
    	return  instance.As<Transform>()->GetWorldMatrix();
    },
    std::nullopt,
    nullptr);
}
#pragma endregion

void Transform::UpdateLocalMatrix()
{
    auto mat = glm::identity<glm::mat4>();
    mat = glm::translate(mat, m_LocalTranslation);
    mat = glm::rotate(mat, glm::angle(m_LocalRotation), glm::axis(m_LocalRotation));
    mat = glm::scale(mat, m_LocalScale);
    m_LocalMatrix = mat;
    m_LocalMatrixIsDirty = false;
}

void Transform::UpdateWorldMatrixAndDecompose()
{
    mat4 mat = GetLocalMatrix();
    Handle<Actor> actor = GetOwnerActor();
    if (Handle<Actor> parent = actor->GetParent())
    {
        if (Handle<Transform> parentTransform = parent->GetComponent<Transform>())
        {
            mat = parentTransform->GetWorldMatrix() * mat;
        }
    }
    m_WorldMatrix = mat;
    m_WorldMatrixIsDirty = false;

    // decompose
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(m_WorldMatrix, m_WorldScale, m_WorldRotation, m_WorldTranslation, skew, perspective);
}

void Transform::MarkWorldTransformAsDirty()
{
    m_WorldMatrixIsDirty = true;
    MarkChildWorldTransformsAsDirty();
}

void Transform::MarkChildWorldTransformsAsDirty()
{
    Handle<Actor> actor = GetOwnerActor();
    const std::vector<Handle<Actor>>& children = actor->GetChildren();
    for (Handle<Actor> child : children)
    {
        if (Handle<Transform> childTransform = child->GetComponent<Transform>())
        {
			childTransform->MarkWorldTransformAsDirty();
		}
	}
}

void Transform::SetLocalTranslation(const vec3& value)
{
    if (m_LocalTranslation == value)
    {
		return;
	}
    m_LocalTranslation = value;
	m_LocalMatrixIsDirty = true;
    m_WorldMatrixIsDirty = true;
}

vec3 Transform::GetLocalTranslation() const
{
    return m_LocalTranslation;
}

void Transform::SetLocalRotation(const quat& value)
{
    if (m_LocalRotation == value)
    {
        return;
    }
    m_LocalRotation = value;
	m_LocalMatrixIsDirty = true;
    m_WorldMatrixIsDirty = true;
}

quat Transform::GetLocalRotation() const
{
   return m_LocalRotation;
}

void Transform::SetLocalScale(const vec3& value)
{
    if (m_LocalScale == value)
    {
		return;
	}
    m_LocalScale = value;
	m_LocalMatrixIsDirty = true;
    m_WorldMatrixIsDirty = true;
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

void Transform::SetWorldTranslation(const vec3& value)
{
}

vec3 Transform::GetWorldTranslation()
{
    if (m_WorldMatrixIsDirty)
    {
        UpdateWorldMatrixAndDecompose();
    }

    return m_WorldTranslation;
}

void Transform::SetWorldRotation(const quat& value)
{

}

quat Transform::GetWorldRotation()
{
	if (m_WorldMatrixIsDirty)
	{
		UpdateWorldMatrixAndDecompose();
	}

    return m_WorldRotation;
}

void Transform::SetWorldScale(const vec3& value)
{
}

vec3 Transform::GetWorldScale()
{
	if (m_WorldMatrixIsDirty)
	{
		UpdateWorldMatrixAndDecompose();
	}

    return m_WorldScale;
}

mat4 Transform::GetWorldMatrix()
{
    if (m_WorldMatrixIsDirty)
    {
		UpdateWorldMatrixAndDecompose();
	}
	return m_WorldMatrix;
}

vec3 Transform::GetForward()
{
    const mat4 matrix = GetWorldMatrix();
    return normalize(glm::vec3(matrix[0][2], matrix[1][2], matrix[2][2]));
}

vec3 Transform::GetUp()
{
    const mat4 matrix = GetWorldMatrix();
    return normalize(glm::vec3(matrix[0][1], matrix[1][1], matrix[2][1]));
}

vec3 Transform::GetRight()
{
    const mat4 matrix = GetWorldMatrix();
    return normalize(glm::vec3(matrix[0][0], matrix[1][0], matrix[2][0]));
}

heliumEnd

