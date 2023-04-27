#include "Helium/HeliumPrecompiled.h"

#include "VertexBufferLayout.h"

heliumBegin

U32 VertexBufferLayout::GetStride() const
{
    return m_Stride;
}

void VertexBufferLayout::AddElement(VertexBufferElement element)
{
    element.Offset = m_CurrentOffset;
    const U32 elementSize = GetElementSizeInBytes(element.Type);
    m_CurrentOffset += elementSize;
    m_Elements.push_back(element);
    m_Stride += elementSize;
}

const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
{
    return m_Elements;
}

heliumEnd
