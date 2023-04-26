#include "Helium/HeliumPrecompiled.h"

#include "ManagedObject.h"
#include "Helium/ObjectModel/RuntimeObjectRegistry.h"

heliumBegin


Bool ManagedObject::IsSerializable() const
{
    return s_IsSerializable;
}

String ManagedObject::GetTypeName() const
{
    return s_TypeName;
}

String ManagedObject::ToString() const
{
    return GetTypeName() + "@" + ToHex(reinterpret_cast<U64>(this));
}

Bool ManagedObject::ClassIsSerializable()
{
    return s_IsSerializable;
}

CRC32 ManagedObject::GetTypeID() const
{
    return s_TypeID;
}

CRC32 ManagedObject::GetClassTypeID()
{
    return s_TypeID;
}

void ManagedObject::Serialize(YAML::Node& out) const
{
    out["TypeID"] = GetClassTypeID();
}

void ManagedObject::Deserialize(const YAML::Node& in)
{
    if (in["TypeID"].as<CRC32>() != GetClassTypeID())
    {
        Assert(false, "Type mismatch");
    }
}

UnsafeHandle<ManagedClassDescriptor> ManagedObject::GetDescriptor() const
{
    return UnsafeHandle<ManagedClassDescriptor>(const_cast<ManagedClassDescriptor*>(&s_TypeDescriptor));
}

UnsafeHandle<ManagedClassDescriptor> ManagedObject::GetClassDescriptor()
{
    return UnsafeHandle<ManagedClassDescriptor>(const_cast<ManagedClassDescriptor*>(&s_TypeDescriptor));
}

Reference <ManagedObject> ManagedObject::StaticConstruct()
{
    return MakeManaged<ManagedObject>();
}


heliumEnd
