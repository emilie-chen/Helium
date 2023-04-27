#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/ObjectModel/ManagedObject.h"

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
        // find its real type
        const auto typeID = in["TypeID"].as<CRC32>();
        const auto providedTypeID = T::GetClassTypeID();
        if (typeID == providedTypeID)
        {
            Reference<T> ref = MakeManaged<T>();
            ref->Deserialize(in);
            return ref;
        }

        // find the type in the registry and deserialize it
        const auto descriptor = TypeRegistry::GetInstance()->GetClassDescriptor(typeID);
        if (descriptor)
        {
            Reference<T> ref = std::dynamic_pointer_cast<T>(Reference<ManagedObject>(descriptor->CreateInstance()));
            ref->Deserialize(in);
            return ref;
        }

        return nullptr;
    }

    template<typename T> requires std::is_base_of_v<ManagedObject, T>
    static Reference<T> Deserialize(const Path& path)
    {
        return Deserialize<T>(YAML::LoadFile(path.string()));
    }

    static void Serialize(const Reference<ManagedObject>& object, const Path& path);
};

heliumEnd
