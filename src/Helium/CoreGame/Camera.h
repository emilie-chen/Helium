#pragma once

#include "Helium/HeliumPrecompiled.h"

#pragma region Includes
#include "Helium/CoreGame/ActorComponent.h"
#pragma endregion

heliumBegin

#pragma region Forward Declarations
#pragma endregion

class Camera : public ActorComponent
{
#pragma region Generated
    MANAGED_CLASS(Camera, ActorComponent, false);
#pragma endregion

#pragma region Managed Properties
public:
private:
    vec3 m_TestProperty;
public:
    void SetTestProperty(const vec3& value) { m_TestProperty = value; }
public:
    vec3 GetTestProperty() const { return m_TestProperty; }
#pragma endregion

};

heliumEnd
