#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "ActorComponent.h"

heliumBegin

class Transform final : public ActorComponent
{
    MANAGED_CLASS(Transform, ActorComponent, false);
public:
    Transform() = default;

    static void RegisterInternalCalls();

#pragma region internal calls
    static MonoObject* ctor(MonoObject* instance);
    static void _GetLocalTranslation(MonoObject* instance, glm::vec3& value);
    static void _SetLocalTranslation(MonoObject* instance, const glm::vec3& value);
#pragma endregion

private:
    glm::vec3 m_LocalTranslation{};
    glm::quat m_LocalRotation = glm::identity<glm::quat>();
    glm::vec3 m_LocalScale{ 1.0f, 1.0f, 1.0f };
};

heliumEnd
