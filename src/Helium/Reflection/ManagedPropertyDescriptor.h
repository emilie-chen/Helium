#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Reflection/PropertyType.h"
#include "Helium/ObjectModel/Handle.h"
#include "Helium/LowLevel/PersistentObjectAllocator.h"

heliumBegin

class ManagedClassDescriptor;
class ManagedEnumDescriptor;

class ManagedPropertyDescriptor final
{
public:
	using self = ManagedPropertyDescriptor;

	ManagedPropertyDescriptor(UnsafeHandle<ManagedClassDescriptor> ownerClass, StringView propertyName, PropertyType PropertyType, TypeErasedGetAccessor getter, std::optional<TypeErasedSetAccessor> setter, std::variant<nullptr_t, UnsafeHandle<ManagedClassDescriptor>, UnsafeHandle<ManagedEnumDescriptor>> descriptor);

	DELETE_COPY_AND_MOVE(ManagedPropertyDescriptor);

	~ManagedPropertyDescriptor()
	{
		__debugbreak();
	}

	UnsafeHandle<ManagedClassDescriptor> GetOwnerClass() const { return m_OwnerClass; }
	String GetName() const { return m_Name; }
	PropertyType GetType() const { return m_Type; }

	template <typename TValue>
	TValue GetValue(Handle<ManagedObject> object) const
	{
		return std::any_cast<TValue>(m_Getter(object));
	}

	Bool SetValue(Handle<ManagedObject> object, std::any value) const;
	UnsafeHandle<ManagedClassDescriptor> GetClassDescriptor() const;
	UnsafeHandle<ManagedEnumDescriptor> GetEnumDescriptor() const;

	Bool IsReadOnly() const { return !m_Setter.has_value(); }

	static constexpr size_t MaxInstanceCount = 10000;

	void* operator new(size_t size)
	{
		assert(size == sizeof(self));
		return PersistentObjectAllocator::Allocate<self>();
	}

	void operator delete(void* ptr)
	{
		PersistentObjectAllocator::Deallocate(static_cast<self*>(ptr));
	}

private:
	UnsafeHandle<ManagedClassDescriptor> m_OwnerClass;
	String m_Name;
	PropertyType m_Type;
	TypeErasedGetAccessor m_Getter;
	std::optional<TypeErasedSetAccessor> m_Setter = nullptr;
	std::variant<nullptr_t, UnsafeHandle<ManagedClassDescriptor>, UnsafeHandle<ManagedEnumDescriptor>> m_TypeDescriptor;
};

heliumEnd
