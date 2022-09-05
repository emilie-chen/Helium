#include "Helium/HeliumPrecompiled.h"

#include "HeliumTypeRegistry.h"
#include "Helium/Reflection/TypeRegistry.h"
#include "Helium/Core/ManagedObject.h"

heliumBegin

void HeliumRegisterClasses()
{
    REGISTER_CLASS(ManagedObject);
}

heliumEnd