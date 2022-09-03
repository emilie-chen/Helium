#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Core/ManagedObject.h"

#include <type_traits>

heliumBegin

struct Serializer final
{
    static String Serialize(const Reference<ManagedObject>& object)
    {
        if (object)
        {
            if (!object->IsSerializable())
            {
                spdlog::warn("Object is not serializable: {}", object->ToString());
                return "";
            }

            YAML::Node out;
            object->Serialize(out);
            return YAML::Dump(out);
        }

        return "null";
    }
};

heliumEnd
