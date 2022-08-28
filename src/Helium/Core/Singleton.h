#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Core/Handle.h"
#include "Helium/Core/Reference.h"

heliumBegin

template <typename T>
class Singleton
{
public:
    static Handle<T> GetInstance();

    void InitializeSingleton(const Reference<T>& reference);

protected:
    inline static Handle<T> m_Instance{};
};


template<typename T>
Handle<T> Singleton<T>::GetInstance()
{
    return m_Instance;
}

template<typename T>
void Singleton<T>::InitializeSingleton(const Reference<T>& reference)
{
    m_Instance = reference;
}

heliumEnd
