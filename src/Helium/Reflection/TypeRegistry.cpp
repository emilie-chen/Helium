#include "Helium/HeliumPrecompiled.h"

#include "TypeRegistry.h"

heliumBegin

void TypeRegistry::RegisterClass(const UnsafeHandle<ManagedClassDescriptor>& classDescriptor)
{
    m_ManagedClasses[classDescriptor->GetClassID()] = classDescriptor;
}

UnsafeHandle<TypeRegistry> TypeRegistry::GetInstance()
{
    if (!s_Instance)
    {
        s_Instance = UnsafeHandle<TypeRegistry>(new TypeRegistry());
    }
    return s_Instance;
}

UnsafeHandle<ManagedClassDescriptor> TypeRegistry::GetClassDescriptor(const CRC32& classID) const
{
    if (m_ManagedClasses.contains(classID))
    {
        return m_ManagedClasses.at(classID);
    }

    return UnsafeHandle<ManagedClassDescriptor>(nullptr);
}

heliumEnd
