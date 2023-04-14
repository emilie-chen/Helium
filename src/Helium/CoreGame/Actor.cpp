#include "Helium/HeliumPrecompiled.h"

#include "Actor.h"
#include "Helium/ObjectModel/RuntimeObjectRegistry.h"

#include <mono/metadata/exception.h>

heliumBegin

void Actor::RegisterInternalCalls()
{
    mono_add_internal_call("Helium.Actor::.ctor", (void*) &Actor::ctor);
    mono_add_internal_call("Helium.Actor::GetComponent_Injected", (void*) &Actor::GetComponent_Injected);
}

MonoObject* Actor::ctor(MonoObject* instance)
{
    Reference<Actor> nativeObj = MakeManaged<Actor>();
    ManagedObject::SetNativeHandle(instance, nativeObj.get());
    RuntimeObjectRegistry::GetInstance()->RegisterObject(instance, nativeObj);
    return instance;
}

MonoObject* Actor::GetComponent_Injected(MonoObject* actorInstance, MonoReflectionType* type)
{
    auto* nativeObj = (Actor*) GetNativeHandle(actorInstance);
    if (!nativeObj)
    {
        mono_raise_exception(mono_get_exception_null_reference());
    }
    MonoType* t = mono_reflection_type_get_type(type);
    if (!t)
    {
        mono_raise_exception(mono_get_exception_argument("", ""));
    }
    MonoClass* klass = mono_class_from_mono_type(t);
    return nullptr;
}

heliumEnd

