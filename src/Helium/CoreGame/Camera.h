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
public:
    mat4 GetViewMatrix();
private:
    F32 m_FOV;
public:
    void SetFOV(const F32& value) { m_FOV = value; }
public:
    F32 GetFOV() const { return m_FOV; }
private:
    F32 m_NearPlane;
public:
    void SetNearPlane(const F32& value) { m_NearPlane = value; }
public:
    F32 GetNearPlane() const { return m_NearPlane; }
private:
    F32 m_FarPlane;
public:
    void SetFarPlane(const F32& value) { m_FarPlane = value; }
public:
    F32 GetFarPlane() const { return m_FarPlane; }
private:
    F32 m_AspectRatio;
public:
    void SetAspectRatio(const F32& value) { m_AspectRatio = value; }
public:
    F32 GetAspectRatio() const { return m_AspectRatio; }
#pragma endregion

public:
    void Update() override;
};

heliumEnd
