#include "Helium/HeliumPrecompiled.h"

#include "MonoRuntime.h"

heliumBegin

void TestInternalCall()
{
    spdlog::info("TestInternalCall");
}

MonoRuntime::MonoRuntime()
{
    m_Domain = mono_jit_init("Helium");
    m_Assembly = mono_domain_assembly_open(m_Domain, "Managed/bin/HeliumManaged.dll");
    mono_domain_assembly_open(m_Domain, "Managed/bin/Debug/HeliumManaged.dll")
    Assert(m_Assembly != nullptr);
    MonoClass* klass = mono_class_from_name(mono_assembly_get_image(m_Assembly), "Helium", "TestBindingClass");
    Assert(klass != nullptr);
    mono_add_internal_call("Helium.TestBindingClass::TestInternalCall", (void*)&TestInternalCall);
    MonoMethod* testManagedMethod = mono_class_get_method_from_name(klass, "TestManagedMethod", 0);
    Assert(testManagedMethod != nullptr);
    MonoObject* exception = nullptr;
    MonoObject* result = mono_runtime_invoke(testManagedMethod, nullptr, nullptr, &exception);
    if (exception)
    {
        MonoClass* exceptionClass = mono_object_get_class(exception);
        Assert(exceptionClass != nullptr)
        MonoClass* exceptionParentClass = mono_class_from_name(mono_assembly_get_image(m_Assembly), "System", "Exception");
        MonoMethod* getMessage = mono_class_get_method_from_name(exceptionParentClass, "get_Message", 0);
        Assert(getMessage != nullptr);
        MonoObject* message = mono_runtime_invoke(getMessage, exception, nullptr, nullptr);
        Assert(message != nullptr);
        auto* str = (MonoString*)message;
        const char* str2 = mono_string_to_utf8(str);
        Assert(str2 != nullptr);
        spdlog::error("Managed exception: {}", str2);
    }
    if (result)
    {
        auto* str = (MonoString*)result;
        const char* str2 = mono_string_to_utf8(str);
        Assert(str2 != nullptr);
        spdlog::info("Managed string: {}", str2);
    }

}

MonoRuntime::~MonoRuntime()
{
    mono_jit_cleanup(m_Domain);
}

heliumEnd

