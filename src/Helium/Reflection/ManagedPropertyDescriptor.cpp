#include "Helium/HeliumPrecompiled.h"

#include "ManagedPropertyDescriptor.h"

heliumBegin

ManagedPropertyDescriptor::ManagedPropertyDescriptor(UnsafeHandle<ManagedClassDescriptor> ownerClass, StringView propertyName, PropertyType PropertyType, TypeErasedGetAccessor getter, std::optional<TypeErasedSetAccessor> setter, std::variant<nullptr_t, UnsafeHandle<ManagedClassDescriptor>, UnsafeHandle<ManagedEnumDescriptor>> descriptor)
	: m_OwnerClass(ownerClass), m_Name(propertyName), m_Type(PropertyType), m_Getter(getter), m_Setter(setter), m_TypeDescriptor(descriptor)
{
}

Bool ManagedPropertyDescriptor::SetValue(Handle<ManagedObject> object, std::any value) const
{
	if (m_Setter.has_value())
	{
		(*m_Setter)(object, value);
		return true;
	}

	return false;
}

UnsafeHandle<ManagedClassDescriptor> ManagedPropertyDescriptor::GetClassDescriptor() const
{
	if (m_Type == PropertyType::Handle)
	{
		return std::get<UnsafeHandle<ManagedClassDescriptor>>(m_TypeDescriptor);
	}

	return nullptr;
}

UnsafeHandle<ManagedEnumDescriptor> ManagedPropertyDescriptor::GetEnumDescriptor() const
{
	if (m_Type == PropertyType::Enum)
	{
		return std::get<UnsafeHandle<ManagedEnumDescriptor>>(m_TypeDescriptor);
	}

	return nullptr;
}


heliumEnd

