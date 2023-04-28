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
    vec3 GetWorldTranslation() const;
public:
    quat GetWorldRotation() const;
public:
    vec3 GetWorldScale() const;
#pragma endregion
public:
    Transform() = default;

private:
    void UpdateLocalMatrix();

private:
    glm::vec3 m_LocalTranslation{};
    glm::quat m_LocalRotation = glm::identity<glm::quat>();
    glm::vec3 m_LocalScale{ 1.0f, 1.0f, 1.0f };
    bool m_LocalMatrixIsDirty = true;
    glm::mat4 m_LocalMatrix = glm::identity<glm::mat4>();
};

heliumEnd
