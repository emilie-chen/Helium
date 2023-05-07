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
    UnsafeHandle<ManagedClassDescriptor> rootComponentClass = GetClassDescriptor(CRC32_COMPUTE("ActorComponent"));
    std::vector<UnsafeHandle<ManagedClassDescriptor>> addableComponents;

    for (const auto& classDescriptorPair : m_ManagedClasses)
    {
		const UnsafeHandle<ManagedClassDescriptor>& classDescriptor = classDescriptorPair.second;
        const String name = classDescriptor->GetClassName();
        if (name == "ActorComponent" || name == "Transform" || name.contains("Abstract"))
        {
            continue;
        }
        if (IsBaseOf(rootComponentClass->GetClassID(), classDescriptor->GetClassID()))
        {
			addableComponents.push_back(classDescriptor);
		}
	}

    return addableComponents;
}

Bool TypeRegistry::IsBaseOf(const CRC32& baseID, const CRC32& derivedID) const
{
    UnsafeHandle<ManagedClassDescriptor> baseDescriptor = GetClassDescriptor(baseID);
    if (!baseDescriptor)
    {
        return false;
    }
    UnsafeHandle<ManagedClassDescriptor> derivedDescriptor = GetClassDescriptor(derivedID);
    while (true)
    {
        if (!derivedDescriptor)
        {
			return false;
		}

        if (derivedDescriptor->GetClassID() == baseDescriptor->GetClassID())
        {
			return true;
		}

        derivedDescriptor = GetClassDescriptor(derivedDescriptor->GetBaseID());
    }
}

UnsafeHandle<ManagedClassDescriptor> TypeRegistry::GetClassDescriptor(const CRC32& classID) const
{
    if (classID == 0)
    {
		return UnsafeHandle<ManagedClassDescriptor>(nullptr);
	}

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
