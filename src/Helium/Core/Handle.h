#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Reference.h"

heliumBegin

/// Weak reference to an object
/// \tparam T Type
template <typename T>
class Handle final
{
public:
    Handle();
    Handle(const std::weak_ptr<T>& value);
    operator std::weak_ptr<T>();
    operator std::weak_ptr<T>() const;
    Reference<T> GetObject();
    Reference<T> GetObject() const;
    Reference<T> operator->();
    Reference<T> operator->() const;

    operator Bool() const;
private:
    std::weak_ptr<T> m_WeakPointer;
};

// invalid handle
template<typename T>
Handle<T>::Handle()
    : m_WeakPointer()
{
}

template<typename T>
Handle<T>::Handle(const std::weak_ptr<T>& value)
{
    Assert(value.lock().get() != nullptr);
    m_WeakPointer = value;
}

template<typename T>
Handle<T>::operator std::weak_ptr<T>()
{
    return m_WeakPointer;
}

template<typename T>
Handle<T>::operator std::weak_ptr<T>() const
{
    return m_WeakPointer;
}

template<typename T>
Reference<T> Handle<T>::GetObject()
{
    return Reference(m_WeakPointer.lock());
}

template<typename T>
Reference<T> Handle<T>::GetObject() const
{
    return Reference(m_WeakPointer.lock());
}

template<typename T>
Reference<T> Handle<T>::operator->()
{
    return GetObject();
}

template<typename T>
Reference<T> Handle<T>::operator->() const
{
    return GetObject();
}

template<typename T>
Handle<T>::operator Bool() const
{
    return m_WeakPointer.operator bool();
}

heliumEnd
