#pragma once

#include <Helium/ObjectModel/ManagedObject.h>
#include "Helium/HeliumPrecompiled.h"

heliumBegin

class Actor : public ManagedObject
{
    MANAGED_CLASS(Actor, ManagedObject, false);
public:
    Actor() = default;

    static MonoObject* InternalConstructor(MonoObject* instance);

    static void RegisterInternalCalls();
};

heliumEnd
