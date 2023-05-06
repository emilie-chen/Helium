#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Utility/CRC32.h"
#include "Helium/ObjectModel/UnsafeHandle.h"

heliumBegin

class ManagedClassDescriptor;
class ManagedEnumDescriptor;

class TypeRegistry final
{
public:
    TypeRegistry() = default;

    DELETE_COPY_AND_MOVE(TypeRegistry);

    void RegisterClass(const UnsafeHandle<ManagedClassDescriptor>& classDescriptor);
    void RegisterEnum(const UnsafeHandle<ManagedEnumDescriptor>& enumDescriptor);
    NODISCARD UnsafeHandle<ManagedClassDescriptor> GetClassDescriptor(const CRC32& classID) const;
    NODISCARD UnsafeHandle<ManagedEnumDescriptor> GetEnumDescriptor(const CRC32& enumID) const;

    NODISCARD static UnsafeHandle<TypeRegistry> GetInstance();

    NODISCARD std::vector<UnsafeHandle<ManagedClassDescriptor>> GetAddableActorComponents() const;

private:
    std::unordered_map<CRC32, UnsafeHandle<ManagedClassDescriptor>> m_ManagedClasses;
    std::unordered_map<CRC32, UnsafeHandle<ManagedEnumDescriptor>> m_ManagedEnums;

    inline static UnsafeHandle<TypeRegistry> s_Instance = UnsafeHandle<TypeRegistry>(nullptr);
};

#define REGISTER_CLASS(className) \
    TypeRegistry::GetInstance()->RegisterClass(className :: GetClassDescriptor()); \
    className :: RegisterMembers();

#define REGISTER_ENUM(enumName) \
    TypeRegistry::GetInstance()->RegisterEnum(enumName##Helper :: GetDescriptor())

heliumEnd
