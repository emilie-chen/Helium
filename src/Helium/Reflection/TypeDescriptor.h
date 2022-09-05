#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Utility/CRC32.h"

heliumBegin

class ManagedObject;

class ManagedClassDescriptor final
{
public:
    ManagedClassDescriptor(const String& className, std::function<Reference<ManagedObject>()> factory);

    NODISCARD String GetClassName() const;
    NODISCARD CRC32 GetClassID() const;
    NODISCARD Reference<ManagedObject> CreateInstance() const;

private:
    String m_ClassName;
    CRC32 m_ClassID;
    std::function<Reference<ManagedObject>()> m_Factory;
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
    TEnum ParseEnum(const String& enumValueString);

    template <typename TValue> requires std::is_enum_v<TValue>
    String GetEnumValueString(const TValue& enumValue);

    template <typename TValue> requires std::is_enum_v<TValue>
    void AddEnumValue(const TValue& enumValue, const String& enumValueString);

private:
    String m_EnumName;
    CRC32 m_EnumID;
    Bimap<U64, String> m_EnumValues;
};

template <typename TEnum>
TEnum ManagedEnumDescriptor::ParseEnum(const String& enumValueString)
{
    return static_cast<TEnum>(m_EnumValues.right.at(enumValueString));
}

template <typename TValue> requires std::is_enum_v<TValue>
String ManagedEnumDescriptor::GetEnumValueString(const TValue& enumValue)
{
    return m_EnumValues.left.at(static_cast<U64>(enumValue));
}

template <typename TValue> requires std::is_enum_v<TValue>
void ManagedEnumDescriptor::AddEnumValue(const TValue& enumValue, const String& enumValueString)
{
    m_EnumValues.insert({ static_cast<U64>(enumValue), enumValueString });
}

heliumEnd
