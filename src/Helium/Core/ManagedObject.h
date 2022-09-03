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
    virtual void Serialize(YAML::Node& out) const;
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

template <typename T, typename ... Args> requires std::is_base_of_v<ManagedObject, T>
Reference<T> MakeManaged(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args) ...);
}

#define DECLARE_SERIALIZE() \
    static_assert(s_IsSerializable);                        \
    virtual void Serialize(YAML::Node& out) const override; \
    virtual void Deserialize(const YAML::Node& in) override;

#define BEGIN_IMPLEMENT_SERIALIZE() \
    {                               \
        YAML::Node superNode;       \
        super::Serialize(superNode);\
        out["Super"] = superNode;   \
        out["TypeID"] = GetClassTypeID(); \
    }

#define END_IMPLEMENT_SERIALIZE()

#define SERIALIZE_REFERENCE(ref) \
    { \
        YAML::Node refOut;       \
        ref->Serialize(refOut);  \
        out[#ref] = refOut;      \
    }

#define SERIALIZE_PLAIN(field) \
    {                          \
        out[#field] = field;   \
    }

heliumEnd