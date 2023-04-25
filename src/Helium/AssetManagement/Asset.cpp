#include "Helium/HeliumPrecompiled.h"

#include "Asset.h"

heliumBegin

String Asset::GetPath() const
{
    return m_Path.string();
}

Asset::Asset(Path path)
    : m_Path(std::move(path))
{
    Assert(std::filesystem::exists(m_Path));
}

heliumEnd