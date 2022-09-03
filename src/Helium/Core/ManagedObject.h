#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Utility/Hex.h"
#include "Helium/Utility/CRC32.h"
#include "yaml-cpp/yaml.h"

heliumBegin

class ManagedObject
{
private:
    constexpr static Bool s_IsSerializable = true;
    constexpr static CRC32 s_TypeID = CRC32_COMPUTE(nameof(ManagedObject));
    constexpr static const char* s_TypeName = nameof(ManagedObject);
public:
    virtual ~ManagedObject() = default;
    NODISCARD virtual Bool IsSerializable() const;
    NODISCARD static Bool ClassIsSerializable();
    NODISCARD virtual String ToString() const;
    NODISCARD virtual String GetTypeName() const;
    NODISCARD virtual CRC32 GetTypeID() const;
    NODISCARD static CRC32 GetClassTypeID();
    virtual void Serialize(YAML::Emitter& out) const;
    virtual void Deserialize(const YAML::Node& in);
};

#define MANAGED_OBJECT(className, superClass, isSerializable) \
    private:                                      \
    constexpr static Bool s_IsSerializable = (isSerializable); \
    constexpr static CRC32 s_TypeID = CRC32_COMPUTE(nameof(className)); \
    constexpr static const char* s_TypeName = nameof(className);    \
    public:                                                   \
    using super = superClass;                                                          \
    NODISCARD virtual Bool IsSerializable() const override { return s_IsSerializable; } \
    NODISCARD static Bool ClassIsSerializable() { return s_IsSerializable; } \
    NODISCARD virtual String ToString() const override { return GetTypeName() + "@" + ToHex(reinterpret_cast<U64>(this)); } \
    NODISCARD virtual String GetTypeName() const override { return s_TypeName; } \
    NODISCARD virtual CRC32 GetTypeID() const override { return s_TypeID; } \
    NODISCARD static CRC32 GetClassTypeID() { return s_TypeID; } \
    private:


heliumEnd
