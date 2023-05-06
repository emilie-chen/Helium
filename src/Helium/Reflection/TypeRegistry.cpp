#include "Helium/HeliumPrecompiled.h"

#include "TypeRegistry.h"

#include "Helium/Reflection/TypeDescriptor.h"

heliumBegin

void TypeRegistry::RegisterClass(const UnsafeHandle<ManagedClassDescriptor>& classDescriptor)
{
    m_ManagedClasses[classDescriptor->GetClassID()] = classDescriptor;
}

void TypeRegistry::RegisterEnum(const UnsafeHandle<ManagedEnumDescriptor>& enumDescriptor)
{
    m_ManagedEnums[enumDescriptor->GetEnumID()] = enumDescriptor;
}

UnsafeHandle<TypeRegistry> TypeRegistry::GetInstance()
{
    if (!s_Instance)
    {
        s_Instance = UnsafeHandle<TypeRegistry>(new TypeRegistry());
    }
    return s_Instance;
}

std::vector<UnsafeHandle<ManagedClassDescriptor>> TypeRegistry::GetAddableActorComponents() const
{
    UnsafeHandle<ManagedClassDescriptor> rootComponentClass = m_ManagedClasses.at(CRC32_COMPUTE("ActorComponent"));
    std::vector<UnsafeHandle<ManagedClassDescriptor>> addableComponents;

    for (const auto& classDescriptorPair : m_ManagedClasses)
    {
		const UnsafeHandle<ManagedClassDescriptor>& classDescriptor = classDescriptorPair.second;
        
	}

    return addableComponents;
}

UnsafeHandle<ManagedClassDescriptor> TypeRegistry::GetClassDescriptor(const CRC32& classID) const
{
    if (m_ManagedClasses.contains(classID))
    {
        return m_ManagedClasses.at(classID);
    }

    return UnsafeHandle<ManagedClassDescriptor>(nullptr);
}

UnsafeHandle<ManagedEnumDescriptor> TypeRegistry::GetEnumDescriptor(const CRC32& enumID) const
{
    if (m_ManagedEnums.contains(enumID))
    {
		return m_ManagedEnums.at(enumID);
	}

    return UnsafeHandle<ManagedEnumDescriptor>(nullptr);
}

heliumEnd
