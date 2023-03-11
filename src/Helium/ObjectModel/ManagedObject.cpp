#include "Helium/HeliumPrecompiled.h"

#include "ManagedObject.h"
#include "Helium/Interop/MonoRuntime.h"
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

void ManagedObject::RegisterInternalCalls()
{
    mono_add_internal_call("Helium.ManagedObject::Destroy", (void*)&ManagedObject::InternalDestroy);
    mono_add_internal_call("Helium.ManagedObject::.ctor", (void*)&ManagedObject::InternalConstructor);
}

void ManagedObject::InternalDestroy(MonoObject* instance)
{
    RuntimeObjectRegistry::GetInstance()->UnregisterObject(instance);
}

MonoObject* ManagedObject::InternalConstructor(MonoObject* instance)
{
    Reference<ManagedObject> nativeObj = MakeManaged<ManagedObject>();
    SetNativeHandle(instance, nativeObj.get());
    nativeObj->m_ManagedInstance = instance;
    RuntimeObjectRegistry::GetInstance()->RegisterObject(instance, nativeObj);
    return instance;
}

void ManagedObject::SetNativeHandle(MonoObject* instance, void* nativeHandle)
{
    MonoClass* cls = mono_class_from_name(mono_assembly_get_image(MonoRuntime::GetInstance()->GetMainAssembly()), "Helium", "ManagedObject");
    MonoClassField* field = mono_class_get_field_from_name(cls, "m_NativeHandle");
    Assert(field != nullptr);
    mono_field_set_value(instance, field, &nativeHandle);
}

heliumEnd
