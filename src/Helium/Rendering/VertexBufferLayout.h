#pragma once

#include "Helium/HeliumPrecompiled.h"
#include <span>

heliumBegin

enum class GraphicsDataType
{
    Invalid = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Int,
    Int2,
    Int3,
    Int4,
    Mat3,
    Mat4
};

enum class VertexBufferElementUsage
{
    Invalid = 0,
    Position,
    Normal,
    Color,
    TexCoord,
};

inline constexpr U32 GetElementSizeInBytes(GraphicsDataType type)
{
    switch (type)
    {
    case GraphicsDataType::Float:
        return sizeof(F32);
    case GraphicsDataType::Float2:
        return sizeof(F32) * 2;
    case GraphicsDataType::Float3:
        return sizeof(F32) * 3;
    case GraphicsDataType::Float4:
        return sizeof(F32) * 4;
    case GraphicsDataType::Int:
        return sizeof(S32);
    case GraphicsDataType::Int2:
        return sizeof(S32) * 2;
    case GraphicsDataType::Int3:
        return sizeof(S32) * 3;
    case GraphicsDataType::Int4:
        return sizeof(S32) * 4;
    case GraphicsDataType::Mat3:
        return sizeof(F32) * 3 * 3;
    case GraphicsDataType::Mat4:
        return sizeof(F32) * 4 * 4;
    default:
        Assert(false);
        return 0;
    }
}

inline constexpr U32 GetElementCount(GraphicsDataType type)
{
    switch (type)
    {
    case GraphicsDataType::Float:
        return 1;
    case GraphicsDataType::Float2:
        return 2;
    case GraphicsDataType::Float3:
        return 3;
    case GraphicsDataType::Float4:
        return 4;
    case GraphicsDataType::Int:
        return 1;
    case GraphicsDataType::Int2:
        return 2;
    case GraphicsDataType::Int3:
        return 3;
    case GraphicsDataType::Int4:
        return 4;
    case GraphicsDataType::Mat3:
        return 3 * 3;
    case GraphicsDataType::Mat4:
        return 4 * 4;
    default:
        Assert(false);
        return 0;
    }
}

inline constexpr U32 GetElementComponentCount(GraphicsDataType type)
{
    switch (type)
    {
    case GraphicsDataType::Float:
        return 1;
    case GraphicsDataType::Float2:
        return 2;
    case GraphicsDataType::Float3:
        return 3;
    case GraphicsDataType::Float4:
        return 4;
    case GraphicsDataType::Int:
        return 1;
    case GraphicsDataType::Int2:
        return 2;
    case GraphicsDataType::Int3:
        return 3;
    case GraphicsDataType::Int4:
        return 4;
    case GraphicsDataType::Mat3:
        return 3;
    case GraphicsDataType::Mat4:
        return 4;
    default:
        Assert(false);
        return 0;
    }
}

struct VertexBufferElement final
{
    GraphicsDataType Type;
    VertexBufferElementUsage Usage;
    bool Normalized;
    U32 Offset;

    VertexBufferElement(GraphicsDataType type, VertexBufferElementUsage usage, bool normalized = false)
        : Type(type)
        , Usage(usage)
        , Normalized(normalized)
        , Offset(0)
    {
    }
};

class VertexBufferLayout final
{
public:
    VertexBufferLayout() = default;

    void AddElement(const VertexBufferElement& element);

    NODISCARD U32 GetStride() const;
    NODISCARD const std::vector<VertexBufferElement>& GetElements() const;
private:
    U32 m_Stride{0};
    std::vector<VertexBufferElement> m_Elements;
};

heliumEnd
