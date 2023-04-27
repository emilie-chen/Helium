#include "Helium/HeliumPrecompiled.h"

#include "TypeDescriptor.h"

#include <utility>

heliumBegin

ManagedClassDescriptor::ManagedClassDescriptor(const String& className, std::function<ManagedObject*()> factory)
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

ManagedObject* ManagedClassDescriptor::CreateInstance() const
{
    return m_Factory();
}

ManagedEnumDescriptor::ManagedEnumDescriptor(const String& enumName)
    : m_EnumName(enumName)
    , m_EnumID(CRC32Compute(enumName.c_str(), enumName.length()))
{

}

String ManagedEnumDescriptor::GetEnumName() const
{
    return m_EnumName;
}

CRC32 ManagedEnumDescriptor::GetEnumID() const
{
    return m_EnumID;
}

Size ManagedEnumDescriptor::GetEnumValueCount() const
{
    return m_EnumValues.size();
}

heliumEnd
