#include "Helium/HeliumPrecompiled.h"

#include "Helium/Application.h"
#include "Helium/AssetManagement/Asset.h"
#include "Helium/AssetManagement/PlainTextFileAsset.h"
#include "Helium/AssetManagement/PlainTextFileAssetDescriptor.h"
#include "Helium/HeliumTypeRegistry.h"
#include "Helium/ObjectModel/ManagedObject.h"
#include "Helium/Rendering/NativeWindow.h"
#include "Helium/Serialization/Serializer.h"

#include "Helium/ObjectModel/ManagedEnum.h"
#include "Helium/AssetManagement/AssetType.h"
#include "Helium/AssetManagement/ShaderSourceFileAsset.h"
#include "Helium/EnginePref.h"
#include <argparse/argparse.hpp>

using namespace Helium;

int main(int argc, char** argv)
{
    // parse args
    /**
     * -d, --debug
     */
    argparse::ArgumentParser program("Helium Engine");
    program.add_argument("-d", "--debug")
        .help("Enable managed debugging")
        .default_value(false)
        .implicit_value(true);

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        spdlog::error(err.what());
        return 1;
    }

    if (program["--debug"] == true)
    {
        EnginePref::Set(PreferenceEntry::ManagedDebug, true);
    }
    else
    {
        EnginePref::Set(PreferenceEntry::ManagedDebug, false);
    }

    std::locale::global(std::locale("en_US.UTF-8"));
    HeliumRegisterClasses();
    Application app{};
    app.Execute();
    return 0;
}
