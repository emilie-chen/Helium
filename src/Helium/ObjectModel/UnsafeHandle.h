#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

/// Unsafe non-null reference to an object
/// \tparam T Type
template <typename T>
class UnsafeHandle final
{
public:
    UnsafeHandle();
    UnsafeHandle(T* value);

    T* GetObject();
    const T* GetObject() const;

    T* operator->();
    const T* operator->() const;

    operator Bool() const;

    Bool operator==(const UnsafeHandle<T>& rhs) const
    {
		return m_Pointer == rhs.m_Pointer;
	}

    Bool operator!=(const UnsafeHandle<T>& rhs) const
    {
		return m_Pointer != rhs.m_Pointer;
	}

private:
    T* m_Pointer;
};

template<typename T>
UnsafeHandle<T>::UnsafeHandle(T* value)
    : m_Pointer(value)
{
}

template<typename T>
T* UnsafeHandle<T>::GetObject()
{
    return m_Pointer;
}

template<typename T>
const T* UnsafeHandle<T>::GetObject() const
{
    return m_Pointer;
}

template<typename T>
T* UnsafeHandle<T>::operator->()
{
    return m_Pointer;
}

template<typename T>
const T* UnsafeHandle<T>::operator->() const
{
    return m_Pointer;
}

template<typename T>
UnsafeHandle<T>::operator Bool() const
{
    return static_cast<Bool>(m_Pointer);
}

template<typename T>
UnsafeHandle<T>::UnsafeHandle()
    : m_Pointer(nullptr)
{
}

heliumEnd
