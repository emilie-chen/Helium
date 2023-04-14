#include "Helium/HeliumPrecompiled.h"

#include "Helium/AssetManagement/AssetDescriptor.h"
#include "Helium/AssetManagement/PlainTextFileAsset.h"
#include "Helium/AssetManagement/PlainTextFileAssetDescriptor.h"
#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/HeliumTypeRegistry.h"
#include "Helium/Reflection/TypeRegistry.h"
#include "Helium/CoreGame/Actor.h"
#include "Helium/CoreGame/ActorComponent.h"

heliumBegin

void HeliumRegisterClasses()
{
    REGISTER_CLASS(Asset);
    REGISTER_CLASS(AssetDescriptor);
    REGISTER_CLASS(ManagedObject);
    REGISTER_CLASS(PlainTextFileAsset);
    REGISTER_CLASS(PlainTextFileAssetDescriptor);
    REGISTER_CLASS(Actor);
    REGISTER_CLASS(ActorComponent);
}

heliumEnd