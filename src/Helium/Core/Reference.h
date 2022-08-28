#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

template <typename T>
class Handle;

/// Strong reference to an object
/// \tparam T Type
template <typename T>
class Reference final
{
public:
    explicit Reference(T* value);
    Reference(const std::shared_ptr<T>& value);
    operator std::shared_ptr<T>();
    operator std::shared_ptr<T>() const;

    T* GetObject();
    const T* GetObject() const;

    T* operator->();
    const T* operator->() const;

    operator Handle<T>();
    operator Handle<T>() const;

    operator Bool() const;

private:
    std::shared_ptr<T> m_SharedPointer;
};

template<typename T>
Reference<T>::Reference(T* value)
{
    Assert(value != nullptr);
    m_SharedPointer = std::shared_ptr<T>(value);
}

template<typename T>
Reference<T>::Reference(const std::shared_ptr<T>& value)
{
    Assert(value.get() != nullptr);
    m_SharedPointer = value;
}

template<typename T>
Reference<T>::operator std::shared_ptr<T>()
{
    return m_SharedPointer;
}

template<typename T>
Reference<T>::operator std::shared_ptr<T>() const
{
    return m_SharedPointer;
}

template<typename T>
T* Reference<T>::GetObject()
{
    return m_SharedPointer.get();
}

template<typename T>
const T* Reference<T>::GetObject() const
{
    return m_SharedPointer.get();
}

template<typename T>
T* Reference<T>::operator->()
{
    return GetObject();
}

template<typename T>
const T* Reference<T>::operator->() const
{
    return GetObject();
}

template<typename T>
Reference<T>::operator Handle<T>()
{
    return Handle<T>(m_SharedPointer);
}

template<typename T>
Reference<T>::operator Handle<T>() const
{
    return Handle<T>(m_SharedPointer);
}

template<typename T>
Reference<T>::operator Bool() const
{
    return m_SharedPointer.operator bool();
}

heliumEnd
