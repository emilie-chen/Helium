#include "Helium/HeliumPrecompiled.h"

#include "Helium/CoreGame/Transform.h"

#include "Helium/ObjectModel/RuntimeObjectRegistry.h"
#include "Helium/ObjectModel/ManagedObject.h"


heliumBegin


void Transform::UpdateLocalMatrix()
{
    auto mat = glm::identity<glm::mat4>();
    mat = glm::scale(mat, m_LocalScale);
    mat = glm::mat4_cast(m_LocalRotation) * mat;
    mat = glm::translate(mat, m_LocalTranslation);
    m_LocalMatrix = mat;
    m_IsDirty = false;
}

glm::mat4 Transform::GetLocalMatrix()
{
    if (m_IsDirty)
    {
        UpdateLocalMatrix();
    }
    return m_LocalMatrix;
}


heliumEnd

