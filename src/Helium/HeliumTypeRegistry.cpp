#include "Helium/HeliumPrecompiled.h"

#include "Helium/HeliumTypeRegistry.h"

#include "Helium/AssetManagement/AssetDescriptor.h"
#include "Helium/AssetManagement/PlainTextFileAsset.h"
#include "Helium/AssetManagement/PlainTextFileAssetDescriptor.h"
#include "Helium/AssetManagement/ShaderSourceFileAsset.h"
#include "Helium/AssetManagement/ShaderSourceFileAssetDescriptor.h"
#include "Helium/CoreGame/AbstractRenderer.h"
#include "Helium/CoreGame/Actor.h"
#include "Helium/CoreGame/ActorComponent.h"
#include "Helium/CoreGame/Camera.h"
#include "Helium/CoreGame/CameraType.h"
#include "Helium/CoreGame/PrimitiveRenderer.h"
#include "Helium/CoreGame/PrimitiveType.h"
#include "Helium/CoreGame/Transform.h"
#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/Reflection/ManagedPropertyDescriptor.h"
#include "Helium/Reflection/PropertyType.h"

heliumBegin

void HeliumRegisterClasses()
{
    REGISTER_CLASS(AbstractRenderer);
    REGISTER_CLASS(Actor);
    REGISTER_CLASS(ActorComponent);
    REGISTER_CLASS(Asset);
    REGISTER_CLASS(AssetDescriptor);
    REGISTER_CLASS(Camera);
    REGISTER_CLASS(ManagedObject);
    REGISTER_CLASS(PlainTextFileAsset);
    REGISTER_CLASS(PlainTextFileAssetDescriptor);
    REGISTER_CLASS(PrimitiveRenderer);
    REGISTER_CLASS(Transform);
    REGISTER_ENUM(CameraType);
    REGISTER_ENUM(PrimitiveType);
    REGISTER_ENUM(PropertyType);
    REGISTER_ENUM(ShaderLanguage);
    REGISTER_ENUM(ShaderType);
}

heliumEnd