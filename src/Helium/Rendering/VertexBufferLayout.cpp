#include "Helium/HeliumPrecompiled.h"

#include "VertexBufferLayout.h"

heliumBegin

U32 VertexBufferLayout::GetStride() const
{
    return m_Stride;
}

void VertexBufferLayout::AddElement(const VertexBufferElement& element)
{
    m_Elements.push_back(element);
    m_Stride += GetElementSizeInBytes(element.Type);
}

const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
{
    return m_Elements;
}

heliumEnd
