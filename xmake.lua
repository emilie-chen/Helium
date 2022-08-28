set_languages("c17", "cxx20")

add_rules("mode.debug", "mode.release")
add_requires("spdlog", "fmt", "glm")

target("Helium")
    set_kind("binary")
    add_files("src/Helium/**.cpp")
    add_includedirs("src")
    set_pcxxheader("src/Helium/HeliumPrecompiled.h")
    if is_mode("debug") then
        add_defines("heliumDebug")
        set_symbols("debug")
        set_optimize("none")
    end
    add_packages("spdlog", "fmt", "glm")
