#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "PlainTextFileAssetDescriptor.h"

heliumBegin

class ShaderSourceFileAssetDescriptor final : public PlainTextFileAssetDescriptor
{
    MANAGED_CLASS(ShaderSourceFileAssetDescriptor, PlainTextFileAssetDescriptor, true);
};

heliumEnd
