#include "Helium/HeliumPrecompiled.h"

#include "ManagedPropertyDescriptor.h"

heliumBegin

ManagedPropertyDescriptor::ManagedPropertyDescriptor(UnsafeHandle<ManagedClassDescriptor> ownerClass, StringView propertyName, PropertyType PropertyType, TypeErasedGetAccessor getter, std::optional<TypeErasedSetAccessor> setter)
	: m_OwnerClass(ownerClass), m_Name(propertyName), m_Type(PropertyType), m_Getter(getter), m_Setter(setter)
{
}

inline Bool ManagedPropertyDescriptor::SetValue(Handle<ManagedObject> object, std::any value) const
{
	if (m_Setter)
	{
		(*m_Setter)(object, value);
		return true;
	}

	return false;
}


heliumEnd

