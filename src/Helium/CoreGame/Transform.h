#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "ActorComponent.h"

heliumBegin

class Transform final : public ActorComponent
{
#pragma region Generated
    MANAGED_CLASS(Transform, ActorComponent, false);
public:
public:
    void SetLocalTranslation(const vec3& value);
public:
    vec3 GetLocalTranslation() const;
public:
    void SetLocalRotation(const quat& value);
public:
    quat GetLocalRotation() const;
public:
    void SetLocalScale(const vec3& value);
public:
    vec3 GetLocalScale() const;
public:
    mat4 GetLocalMatrix();
public:
    void SetWorldTranslation(const vec3& value);
public:
    vec3 GetWorldTranslation();
public:
    void SetWorldRotation(const quat& value);
public:
    quat GetWorldRotation();
public:
    void SetWorldScale(const vec3& value);
public:
    vec3 GetWorldScale();
public:
    mat4 GetWorldMatrix();
#pragma endregion
public:
    Transform() = default;

private:
    void UpdateLocalMatrix();
    void UpdateWorldMatrixAndDecompose();
    void MarkWorldTransformAsDirty();
    void MarkChildWorldTransformsAsDirty();

private:
    glm::vec3 m_LocalTranslation{};
    glm::quat m_LocalRotation = glm::identity<glm::quat>();
    glm::vec3 m_LocalScale{ 1.0f, 1.0f, 1.0f };
    bool m_LocalMatrixIsDirty = true;
    glm::mat4 m_LocalMatrix = glm::identity<glm::mat4>();
    bool m_WorldMatrixIsDirty = true;
    glm::mat4 m_WorldMatrix = glm::identity<glm::mat4>();
    glm::vec3 m_WorldTranslation{};
    glm::quat m_WorldRotation = glm::identity<glm::quat>();
    glm::vec3 m_WorldScale{ 1.0f, 1.0f, 1.0f };
};

heliumEnd
