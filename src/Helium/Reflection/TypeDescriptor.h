#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Utility/CRC32.h"
#include "Helium/ObjectModel/UnsafeHandle.h"
#include "Helium/ObjectModel/Handle.h"

heliumBegin

class ManagedObject;
class ManagedPropertyDescriptor;
class ManagedClassDescriptor;
class ManagedEnumDescriptor;
enum class PropertyType;

using TypeErasedGetAccessor = std::function<std::any(Handle<ManagedObject>)>;
using TypeErasedSetAccessor = std::function<void(Handle<ManagedObject>, std::any)>;

class ManagedClassDescriptor final
{
public:
    using self = ManagedClassDescriptor;

    ManagedClassDescriptor(const String& className, std::function<ManagedObject*()> factory);

    NODISCARD String GetClassName() const;
    NODISCARD CRC32 GetClassID() const;
    NODISCARD ManagedObject* CreateInstance() const;

    void AddProperty(StringView propertyName, PropertyType propertyType, TypeErasedGetAccessor getter, std::optional<TypeErasedSetAccessor> setter, std::variant<nullptr_t, UnsafeHandle<ManagedClassDescriptor>, UnsafeHandle<ManagedEnumDescriptor>> descriptor);
    std::vector<UnsafeHandle<ManagedPropertyDescriptor>> GetProperties() const;

private:
    String m_ClassName;
    CRC32 m_ClassID;
    std::function<ManagedObject*()> m_Factory;
    std::vector<UnsafeHandle<ManagedPropertyDescriptor>> m_Properties;
};

class ManagedInterfaceDescriptor final
{

};

class ManagedEnumDescriptor final
{
public:
    explicit ManagedEnumDescriptor(const String& enumName);

    NODISCARD String GetEnumName() const;
    NODISCARD CRC32 GetEnumID() const;

    template <typename TEnum>
    NODISCARD TEnum ParseEnum(const String& enumValueString) const;

    template <typename TValue>
    NODISCARD String GetEnumValueString(const TValue& enumValue) const;

    template <typename TValue>
    void AddEnumValue(const TValue& enumValue, const String& enumValueString);

    NODISCARD Size GetEnumValueCount() const;

    NODISCARD std::vector<std::pair<String, U64>> GetEnumPairs() const;

private:
    String m_EnumName;
    CRC32 m_EnumID;
    Bimap<U64, String> m_EnumValues;
};

template <typename TEnum>
TEnum ManagedEnumDescriptor::ParseEnum(const String& enumValueString) const
{
    return static_cast<TEnum>(m_EnumValues.right.at(enumValueString));
}

template <typename TValue>
String ManagedEnumDescriptor::GetEnumValueString(const TValue& enumValue) const
{
    return m_EnumValues.left.at(static_cast<U64>(enumValue));
}

template <typename TValue>
void ManagedEnumDescriptor::AddEnumValue(const TValue& enumValue, const String& enumValueString)
{
    m_EnumValues.insert({ static_cast<U64>(enumValue), enumValueString });
}

heliumEnd
