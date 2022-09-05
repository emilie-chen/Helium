#include "Helium/HeliumPrecompiled.h"

#include "Serializer.h"
#include <fstream>

heliumBegin

String Serializer::Serialize(const Reference<ManagedObject>& object)
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

void Serializer::Serialize(const Reference <ManagedObject>& object, const Path& path)
{
    String data = Serialize(object);
    std::ofstream file(path);
    file << data;
}

heliumEnd
