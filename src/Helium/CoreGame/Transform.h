#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

class Transform final
{
private:
    glm::vec3 m_Position;
    glm::quat m_Rotation;
    glm::vec3 m_Scale;
};

heliumEnd
