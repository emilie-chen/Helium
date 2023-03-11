#include "Helium/HeliumPrecompiled.h"

#include "Actor.h"
#include "Helium/ObjectModel/RuntimeObjectRegistry.h"

heliumBegin

void Actor::RegisterInternalCalls()
{
    mono_add_internal_call("Helium.Actor::.ctor", (void*)&Actor::InternalConstructor);
}

MonoObject* Actor::InternalConstructor(MonoObject* instance)
{
    Reference<Actor> nativeObj = MakeManaged<Actor>();
    ManagedObject::SetNativeHandle(instance, nativeObj.get());
    RuntimeObjectRegistry::GetInstance()->RegisterObject(instance, nativeObj);
    return instance;
}

heliumEnd

