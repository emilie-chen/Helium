#include "Helium/HeliumPrecompiled.h"

#include "TypeDescriptor.h"

#include <utility>

heliumBegin

ManagedClassDescriptor::ManagedClassDescriptor(const String& className, std::function<Reference<ManagedObject>()> factory)
    : m_ClassName(className)
    , m_ClassID(CRC32Compute(className.c_str(), className.length()))
    , m_Factory(std::move(factory))
{
}

String ManagedClassDescriptor::GetClassName() const
{
    return m_ClassName;
}

CRC32 ManagedClassDescriptor::GetClassID() const
{
    return m_ClassID;
}

Reference <ManagedObject> ManagedClassDescriptor::CreateInstance() const
{
    return m_Factory();
}

heliumEnd
