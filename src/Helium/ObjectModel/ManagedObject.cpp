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

MonoObject* ManagedObject::InternalInstantiate(MonoString* ns, MonoString* typeName)
{
    // instantiate the managed object
    char* typeNameStr = mono_string_to_utf8(typeName);
    char* nsStr = mono_string_to_utf8(ns);
    Reference<ManagedObject> obj = MakeManaged<ManagedObject>();
    MonoClass* cls = mono_class_from_name(mono_assembly_get_image(MonoRuntime::GetInstance()->GetMainAssembly()), nsStr, typeNameStr);
    //spdlog::trace("Instantiated managed object of type {} in {}. Native handle: {}", typeNameStr, nsStr, (size_t)obj.get());
    mono_free(typeNameStr);
    mono_free(nsStr);
    Assert(cls != nullptr);
    MonoObject* monoObj = mono_object_new(mono_domain_get(), cls);
    Assert(monoObj != nullptr);
    mono_runtime_object_init(monoObj);

    // set the managed object's native pointer
    MonoClassField* field = mono_class_get_field_from_name(cls, "m_NativeHandle");
    Assert(field != nullptr);
    void* ptr = obj.get();
    mono_field_set_value(monoObj, field, &ptr);
    obj->m_ManagedInstance = monoObj;

    RuntimeObjectRegistry::GetInstance()->RegisterObject(monoObj, obj);

    return monoObj;
}

void ManagedObject::RegisterInternalCalls()
{
    mono_add_internal_call("Helium.ManagedObject::InternalInstantiate", (void*)&ManagedObject::InternalInstantiate);
    mono_add_internal_call("Helium.ManagedObject::Destroy", (void*)&ManagedObject::InternalDestroy);
}

void ManagedObject::InternalDestroy(MonoObject* instance)
{
    RuntimeObjectRegistry::GetInstance()->UnregisterObject(instance);
}

heliumEnd
