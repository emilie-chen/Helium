#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Reflection/PropertyType.h"
#include "Helium/ObjectModel/Handle.h"

heliumBegin

class ManagedClassDescriptor;
class ManagedEnumDescriptor;

class ManagedPropertyDescriptor final
{
public:
	ManagedPropertyDescriptor(UnsafeHandle<ManagedClassDescriptor> ownerClass, StringView propertyName, PropertyType PropertyType, TypeErasedGetAccessor getter, std::optional<TypeErasedSetAccessor> setter);

	DELETE_COPY_AND_MOVE(ManagedPropertyDescriptor);

	UnsafeHandle<ManagedClassDescriptor> GetOwnerClass() const { return m_OwnerClass; }
	String GetName() const { return m_Name; }
	PropertyType GetType() const { return m_Type; }

	template <typename TValue>
	TValue GetValue(Handle<ManagedObject> object) const
	{
		return std::any_cast<TValue>(m_Getter(object));
	}

	Bool SetValue(Handle<ManagedObject> object, std::any value) const;

private:
	UnsafeHandle<ManagedClassDescriptor> m_OwnerClass;
	String m_Name;
	PropertyType m_Type;
	TypeErasedGetAccessor m_Getter;
	std::optional<TypeErasedSetAccessor> m_Setter;
};

heliumEnd
