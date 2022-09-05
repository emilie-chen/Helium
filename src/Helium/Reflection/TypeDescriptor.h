#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Utility/CRC32.h"

heliumBegin

class ManagedObject;

class ManagedClassDescriptor final
{
public:
    ManagedClassDescriptor(const String& className, std::function<Reference<ManagedObject>()> factory);

    NODISCARD String GetClassName() const;
    NODISCARD CRC32 GetClassID() const;
    NODISCARD Reference<ManagedObject> CreateInstance() const;

private:
    String m_ClassName;
    CRC32 m_ClassID;
    std::function<Reference<ManagedObject>()> m_Factory;
};

class ManagedInterfaceDescriptor final
{

};

heliumEnd
