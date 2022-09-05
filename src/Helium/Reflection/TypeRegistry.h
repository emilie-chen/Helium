#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Utility/CRC32.h"
#include "Helium/Core/UnsafeHandle.h"
#include "TypeDescriptor.h"

heliumBegin

class TypeRegistry final
{
public:
    TypeRegistry() = default;

    DELETE_COPY_AND_MOVE(TypeRegistry);

    void RegisterClass(const UnsafeHandle<ManagedClassDescriptor>& classDescriptor);
    NODISCARD UnsafeHandle<ManagedClassDescriptor> GetClassDescriptor(const CRC32& classID) const;

    NODISCARD static UnsafeHandle<TypeRegistry> GetInstance();

private:
    std::unordered_map<CRC32, UnsafeHandle<ManagedClassDescriptor>> m_ManagedClasses;

    inline static UnsafeHandle<TypeRegistry> s_Instance = UnsafeHandle<TypeRegistry>(nullptr);
};

#define REGISTER_CLASS(className) \
    TypeRegistry::GetInstance()->RegisterClass(className :: GetClassDescriptor())

heliumEnd
