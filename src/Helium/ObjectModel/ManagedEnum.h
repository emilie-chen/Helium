#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Reflection/TypeDescriptor.h"

#include "Helium/ObjectModel/UnsafeHandle.h"
#include "Helium/LowLevel/PersistentObjectAllocator.h"

heliumBegin

template <typename T>
struct DeduceEnumHelper
{
};

#define BEGIN_ENUM_REGISTRATION(enumClass) \
class enumClass##Helper;                   \
                                           \
template <>                                \
struct DeduceEnumHelper<enumClass>         \
{                                          \
    using Type = enumClass##Helper;        \
};                                         \
                                           \
class enumClass##Helper final              \
{                                          \
public:                                    \
    using HelperType = enumClass##Helper;  \
    using EnumType = enumClass;            \
private:                                   \
    static constexpr auto EnumName = #enumClass;  \
private:                                    \
    enumClass##Helper()                    \
    {

#define REGISTER_ENUM_VALUE(enumValue) \
    m_Descriptor.AddEnumValue(EnumType::enumValue, #enumValue);

#define END_ENUM_REGISTRATION() \
    }                           \
public:                         \
    static UnsafeHandle<ManagedEnumDescriptor> GetDescriptor() \
    {                           \
        if (!s_Helper)          \
        {                       \
            s_Helper = Reference<HelperType>(new HelperType);  \
        }                       \
        return UnsafeHandle<ManagedEnumDescriptor>(&s_Helper->m_Descriptor);  \
    } \
private:                        \
    inline static Reference<HelperType> s_Helper{}; \
    ManagedEnumDescriptor m_Descriptor{EnumName};             \
public:\
    void* operator new(size_t size) \
    { return PersistentObjectAllocator::Allocate<HelperType>(); } \
    void operator delete(void* ptr) \
    { PersistentObjectAllocator::Deallocate(ptr); }   \
};


heliumEnd
