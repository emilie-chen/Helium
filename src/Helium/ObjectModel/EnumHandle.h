#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/ObjectModel/UnsafeHandle.h"
#include "Helium/ObjectModel/ManagedEnum.h"

heliumBegin

class ManagedEnumDescriptor;

template <typename T1, typename T2>
struct EqualSize
{
	static constexpr bool Value = sizeof(T1) == sizeof(T2);
};

class EnumHandleRef final
{
private:
	EnumHandleRef() = default;

public:
	U64 GetValue() const { return Value; }
	UnsafeHandle<ManagedEnumDescriptor> GetDescriptor() const { return Descriptor; }

private:
	UnsafeHandle<ManagedEnumDescriptor> Descriptor;
	U64 Value;

	template <typename T> requires std::is_enum_v<T>
	friend class EnumHandle;
};

template <typename T> requires std::is_enum_v<T>
class EnumHandle final
{
public:
	EnumHandle(T value) requires EqualSize<T, U64>::Value
	{
		m_Value = reinterpret_cast<U64&>(value);
	}

	EnumHandle(T value) requires (!EqualSize<T, U64>::Value)
	{
		m_Value = static_cast<U64>(value);
	}

	UnsafeHandle<ManagedEnumDescriptor> GetDescriptor() const
	{
		return DeduceEnumHelper<T>::Type::GetDescriptor();
	}

	U64 GetValue() const
	{
		return m_Value;
	}

	EnumHandleRef ToRef() const
	{
		EnumHandleRef ref;
		ref.Descriptor = GetDescriptor();
		ref.Value = m_Value;
		return ref;
	}

private:
	U64 m_Value;
};

heliumEnd
