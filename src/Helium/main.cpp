#include "Helium/HeliumPrecompiled.h"
#include "Helium/Application.h"
#include "Helium/Rendering/NativeWindow.h"
#include "Helium/AssetManagement/Asset.h"
#include "Helium/Core/ManagedObject.h"

int main()
{
    using namespace Helium;
    Application app{};
    app.Execute();
    return 0;
}
