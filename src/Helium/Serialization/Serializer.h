#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Core/ManagedObject.h"

#include <type_traits>

heliumBegin

struct Serializer final
{
    static String Serialize(const Reference<ManagedObject>& object);

    template<typename T> requires std::is_base_of_v<ManagedObject, T>
    static Reference<T> Deserialize(const String& data)
    {
        return Deserialize<T>(YAML::Load(data));
    }

    template<typename T> requires std::is_base_of_v<ManagedObject, T>
    static Reference<T> Deserialize(const YAML::Node& in)
    {
        if (in.IsNull())
        {
            return nullptr;
        }
        Reference<T> ref = MakeManaged<T>();
        ref->Deserialize(in);
        return ref;
    }
};

heliumEnd
