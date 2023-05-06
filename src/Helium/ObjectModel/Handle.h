#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/InstanceID.h"

heliumBegin

template <typename T>
class Handle;

class ManagedObject;
Bool IsObjectValid(Handle<ManagedObject> instance);

/**
 * @brief A handle to a managed object. Managed objects are not reference counted and are destroyed via Object::Destroy()
 * @tparam T
 */
template <typename T>
class Handle final
{
public:
    Handle()
        : m_Object(nullptr), m_InstanceID(DefaultInstanceID)
    {

    }

    Handle(T* object)
        : m_Object(object), m_InstanceID(object ? object->GetInstanceID() : 0)
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
        return IsValid();
    }

    Bool IsValid() const
    {
        if (m_Object == nullptr)
        {
			return false;
		}
        const Bool result = IsObjectValid(static_cast<Handle<ManagedObject>>(*this));
        if (!result)
        {
			m_Object = nullptr;
			m_InstanceID = DefaultInstanceID;
		}
        return result;
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

    template <typename U>
    Handle<U> As() const
    {
        return Handle<U>(dynamic_cast<U*>(m_Object));
    }

    template <typename U>
    Handle<U> As()
    {
        return Handle<U>(dynamic_cast<U*>(m_Object));
    }

    template <typename U>
    Bool Is() const
    {
		return dynamic_cast<U*>(m_Object) != nullptr;
	}

    template <typename U>
    bool operator==(const Handle<U>& other) const
    {
        return m_Object == other.m_Object;
    }

    template <typename U>
    bool operator!=(const Handle<U>& other) const
    {
		return m_Object != other.m_Object;
	}

    template <typename U>
    bool operator==(const U* other) const
    {
		return m_Object == other;
	}

    template <typename U>
    bool operator!=(const U* other) const
    {
        return m_Object != other;
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

    template <typename U> requires (!std::is_base_of_v<U, T>)
    explicit operator Handle<U>()
    {
        return Handle<U>(dynamic_cast<U*>(m_Object));
    }

    template <typename U> requires (!std::is_base_of_v<U, T>)
    explicit operator Handle<U>() const
    {
		return Handle<U>(dynamic_cast<U*>(m_Object));
	}

    InstanceID GetHandleInstanceID() const
    {
		return m_InstanceID;
	}

private:
    mutable T* m_Object = nullptr;
    mutable InstanceID m_InstanceID;
};

heliumEnd

namespace std {

template <typename T>
struct hash<Helium::Handle<T>>
{
    std::size_t operator()(const Helium::Handle<T>& k) const
    {
        return std::hash<T*>()(k.Get());
    }
};

}
