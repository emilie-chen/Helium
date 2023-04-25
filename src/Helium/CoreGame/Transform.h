#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "ActorComponent.h"

heliumBegin

class Transform final : public ActorComponent
{
    MANAGED_CLASS(Transform, ActorComponent, false);
    MONO_CLASS_DEFINE(Transform)
public:
    Transform() = default;

    static void RegisterInternalCalls();

#pragma region internal calls
    static void _GetLocalTranslation(MonoObject* instance, glm::vec3& value);
    static void _SetLocalTranslation(MonoObject* instance, const glm::vec3& value);
    static void _GetLocalRotation(MonoObject* instance, glm::quat& value);
    static void _SetLocalRotation(MonoObject* instance, const glm::quat& value);
    static void _GetLocalScale(MonoObject* instance, glm::vec3& value);
    static void _SetLocalScale(MonoObject* instance, const glm::vec3& value);
    static void _GetLocalMatrix(MonoObject* instance, glm::mat4& value);
#pragma endregion

    [[nodiscard]] glm::vec3 GetLocalTranslation() const { return m_LocalTranslation; }
    void SetLocalTranslation(const glm::vec3& value) { m_LocalTranslation = value; m_IsDirty = true; }

    [[nodiscard]] glm::quat GetLocalRotation() const { return m_LocalRotation; }
    void SetLocalRotation(const glm::quat& value) { m_LocalRotation = value; m_IsDirty = true; }

    [[nodiscard]] glm::vec3 GetLocalScale() const { return m_LocalScale; }
    void SetLocalScale(const glm::vec3& value) { m_LocalScale = value; m_IsDirty = true; }

    [[nodiscard]] glm::mat4 GetLocalMatrix();
private:
    void UpdateLocalMatrix();

private:
    glm::vec3 m_LocalTranslation{};
    glm::quat m_LocalRotation = glm::identity<glm::quat>();
    glm::vec3 m_LocalScale{ 1.0f, 1.0f, 1.0f };
    bool m_IsDirty = true;
    glm::mat4 m_LocalMatrix = glm::identity<glm::mat4>();
};

heliumEnd
