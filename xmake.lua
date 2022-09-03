set_languages("c17", "cxx20")
set_allowedarchs("x64")
set_defaultarchs("x64")

add_rules("mode.debug", "mode.release")
add_requires("vcpkg::spdlog", "vcpkg::fmt", "vcpkg::glm", "opengl", "vcpkg::glad", "vcpkg::glfw3", "vcpkg::imgui[core,glfw-binding,opengl3-binding]", "vcpkg::yaml-cpp")

target("Helium")
    set_kind("binary")
    add_files("src/Helium/**.cpp")
    add_headerfiles("src/Helium/**.h")
    add_includedirs("src")
    set_pcxxheader("src/Helium/HeliumPrecompiled.h")
    if is_mode("debug") then
        add_defines("heliumDebug")
        set_symbols("debug")
        set_optimize("none")
    end
    add_packages("vcpkg::spdlog", "vcpkg::fmt", "vcpkg::glm", "opengl", "vcpkg::glad", "vcpkg::glfw3", "vcpkg::imgui[core,glfw-binding,opengl3-binding]", "vcpkg::yaml-cpp")
    if is_plat("macosx") then
        add_frameworks("Cocoa", "IOKit")
    end
