#include "Helium/HeliumPrecompiled.h"
#include "Helium/Application.h"
#include "Helium/Rendering/NativeWindow.h"
#include "Helium/AssetManagement/Asset.h"
#include "Helium/Core/ManagedObject.h"
#include "Helium/Serialization/Serializer.h"
#include "Helium/HeliumTypeRegistry.h"

using namespace Helium;

int main()
{
    HeliumRegisterClasses();
    Application app{};
    app.Execute();
    return 0;
}
