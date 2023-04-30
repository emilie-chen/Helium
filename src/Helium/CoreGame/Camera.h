#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/CoreGame/ActorComponent.h"
#include "Helium/CoreGame/CameraType.h"

heliumBegin

class Camera : public ActorComponent
{
#pragma region Generated
    MANAGED_CLASS(Camera, ActorComponent, false);
public:
private:
    CameraType m_CameraType;
public:
    void SetCameraType(const CameraType& value) { m_CameraType = value; }
public:
    CameraType GetCameraType() const { return m_CameraType; }
public:
    mat4 GetProjectionMatrix();
#pragma endregion
};

heliumEnd
