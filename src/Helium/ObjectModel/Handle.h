#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/ManagedObject.h"

heliumBegin

/**
 * @brief A handle to a managed object. Managed objects are not reference counted and are destroyed via Object::Destroy()
 * @tparam T
 */
template <typename T> requires std::is_base_of_v<ManagedObject, T>
class Handle final
{
public:
    Handle() = default;

    Handle(T* object)
        : m_Object(object)
    {
    }

    T* operator->() const
    {
        return m_Object;
    }

    T& operator*() const
    {
        return *m_Object;
    }

    T* Get() const
    {
        return m_Object;
    }

    operator bool() const
    {
        // check object validity in runtime object registry

        return m_Object != nullptr;
    }

    // non const
    T* operator->()
    {
        return m_Object;
    }

    T& operator*()
    {
        return *m_Object;
    }

    T* Get()
    {
        return m_Object;
    }

    template <typename U> requires std::is_base_of_v<ManagedObject, U>
    Handle<U> As() const
    {
        return Handle<U>(dynamic_cast<U*>(m_Object));
    }

    template <typename U> requires std::is_base_of_v<ManagedObject, U>
    Handle<U> As()
    {
        return Handle<U>(dynamic_cast<U*>(m_Object));
    }

    template <typename U> requires std::is_base_of_v<ManagedObject, U>
    bool operator==(const Handle<U>& other) const
    {
        return m_Object == other.m_Object;
    }

    template <typename U> requires std::is_base_of_v<U, T>
    operator Handle<U>() const
    {
        return Handle<U>(static_cast<U*>(m_Object));
    }

    template <typename U> requires std::is_base_of_v<U, T>
    operator Handle<U>()
    {
        return Handle<U>(static_cast<U*>(m_Object));
    }

private:
    T* m_Object = nullptr;
};

heliumEnd

namespace std {

template <typename T> requires std::is_base_of_v<Helium::ManagedObject, T>
struct hash<Helium::Handle<T>>
{
    std::size_t operator()(const Helium::Handle<T>& k) const
    {
        return std::hash<T*>()(k.Get());
    }
};

}
