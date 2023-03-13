#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/ObjectModel/ManagedObject.h"

heliumBegin

class ActorComponent : public ManagedObject
{
    MANAGED_CLASS(ActorComponent, ManagedObject, false);
};

heliumEnd
