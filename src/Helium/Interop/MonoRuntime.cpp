#include "Helium/HeliumPrecompiled.h"

#include "MonoRuntime.h"
#include "Helium/Interop/Bindings/Helium/Debug.h"

heliumBegin

void TestInternalCall()
{
    spdlog::info("TestInternalCall");
    Assert(false);
}

void EngineLog(MonoString* message)
{
    spdlog::info("{}", mono_string_to_utf8(message));
}

MonoRuntime::MonoRuntime()
{
    m_Domain = mono_jit_init("Helium");
    // get all assemblies in folder
    std::string path = "Managed/bin/";
    std::string extension = ".dll";
    // get all files in folder
    for (auto &p : std::filesystem::recursive_directory_iterator(path))
    {
        if (p.path().extension() == extension)
        {
            std::string assemblyPath = p.path().string();
            MonoAssembly* assembly = mono_domain_assembly_open(m_Domain, assemblyPath.c_str());
            if (assembly == nullptr)
            {
                spdlog::error("Failed to load assembly: {}", assemblyPath);
                continue;
            }
            else
            {
                spdlog::info("Loaded assembly: {}", assemblyPath);
            }
            std::string stem = p.path().stem().string();
            if (stem == "HeliumManaged")
            {
                m_MainAssembly = assembly;
            }
            m_LoadedAssemblies.left.insert({stem, assembly});
        }
    }
    Assert(m_MainAssembly != nullptr);

    // register internal calls
    Debug::RegisterInternalCalls();

    // test method
    MonoImage* image = mono_assembly_get_image(m_MainAssembly);
    MonoClass* klass = mono_class_from_name(image, "Helium", "TestBindingClass");
    MonoMethod* method = mono_class_get_method_from_name(klass, "TestManagedMethod", 0);

    MonoObject* exception = nullptr;
    mono_runtime_invoke(method, nullptr, nullptr, &exception);
}

MonoRuntime::~MonoRuntime()
{
    mono_jit_cleanup(m_Domain);
}

heliumEnd

