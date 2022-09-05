#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "PlainTextFileAsset.h"

heliumBegin

class ShaderSourceFileAsset final : public PlainTextFileAsset
{
    MANAGED_CLASS(ShaderSourceFileAsset, PlainTextFileAsset, true);

};

heliumEnd
