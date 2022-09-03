#include "Helium/HeliumPrecompiled.h"

#include "ManagedObject.h"

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

void ManagedObject::Serialize(YAML::Emitter& out) const
{
    out << YAML::BeginMap;
    out << YAML::Key << "Type" << YAML::Value << GetTypeName();
    out << YAML::EndMap;
}

void ManagedObject::Deserialize(const YAML::Node& in)
{
    // Nothing to do
}

heliumEnd
