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

using namespace Helium;

int main()
{
    std::locale::global(std::locale(""));
    HeliumRegisterClasses();
    Reference<PlainTextFileAsset> asset = MakeManaged<PlainTextFileAsset>("Assets/testfile.txt");
    asset->Load();
    WString text = asset->GetText();
    spdlog::info("{}", String(text.begin(), text.end()));
    asset->SetText(L"Hello, Hallo, Bonjour, 你好");
    asset->Save();
    Application app{};
    app.Execute();
    return 0;
}
