#include "Helium/HeliumPrecompiled.h"

#include "Actor.h"
#include "Helium/ObjectModel/RuntimeObjectRegistry.h"
#include "Helium/Interop/MonoRuntime.h"

#include <mono/metadata/exception.h>

heliumBegin

void Actor::RegisterInternalCalls()
{
    mono_add_internal_call("Helium.Actor::GetComponent_Injected", (void*) &Actor::GetComponent_Injected);
    LINK_MANAGED_CLASS();
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

void Actor::Awake()
{

}

void Actor::Start()
{

}

void Actor::Update()
{

}

void Actor::FixedUpdate()
{

}

void Actor::OnDestroy()
{

}

void Actor::DestroyChildObjects()
{
    base::DestroyChildObjects();
}

Actor::Actor()
{

}

Actor::~Actor()
{

}

heliumEnd

