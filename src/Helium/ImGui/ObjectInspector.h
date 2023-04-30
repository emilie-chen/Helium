#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "ImGuiWindow.h"

heliumBegin

class ObjectInspector final
{
public:
    ObjectInspector() = delete;

    static void Inspect(Handle<ManagedObject> object);
};

heliumEnd
