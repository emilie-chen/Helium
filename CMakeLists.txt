cmake_minimum_required(VERSION 3.20.0)

project(Helium VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# print architecture
message(STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")

add_executable(Helium)
add_compile_options("/MP")

find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(EASTL CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(argparse REQUIRED)
find_package(cppcoro REQUIRED)
find_package(imguizmo REQUIRED)

set(HELIUM_WORKING_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/imgui)

target_compile_definitions(
        Helium
        PUBLIC
        BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
        heliumDebug
        BOOST_STACKTRACE_USE_ADDR2LINE
)

target_include_directories(Helium PUBLIC
    ${Boost_INCLUDE_DIRS})

IF(WIN32)
target_link_libraries(Helium PUBLIC fmt::fmt
    glad::glad
    glfw
    IMGUI
    yaml-cpp
    argparse::argparse
    EASTL
    cppcoro
    imguizmo::imguizmo
)
ELSE()
target_link_libraries(Helium PUBLIC fmt::fmt
    glad::glad
    glfw
    IMGUI
    yaml-cpp
    argparse::argparse
    EASTL
    dl
    l
    "-framework Cocoa"
    "-framework IOKit"
    "-framework OpenGL"
    z
)
ENDIF()

target_link_libraries(Helium PUBLIC spdlog::spdlog spdlog::spdlog_header_only)

# find all headers and source files
file(GLOB_RECURSE HELIUM_HEADERS CONFIGURE_DEPENDS src/Helium/*.h)
file(GLOB_RECURSE HELIUM_SOURCES CONFIGURE_DEPENDS src/Helium/*.cpp src/Helium/*.declaration.cs)
set(HELIUM_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src/Helium)

# pch
target_precompile_headers(Helium PUBLIC src/Helium/HeliumPrecompiled.h)

target_include_directories(Helium PUBLIC
    src
    ${IMGUI_INCLUDE_DIRS}
)


message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")


target_sources(Helium PUBLIC
    ${HELIUM_HEADERS}
    ${HELIUM_SOURCES}
)

message(STATUS ${CMAKE_CURRENT_LIST_DIR})

set_property(TARGET Helium PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

IF(WIN32)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR}/src FILES ${HELIUM_HEADERS} ${HELIUM_SOURCES} PREFIX src)

file(GLOB_RECURSE HELIUM_ASSETS Assets/*)
target_sources(Helium PUBLIC ${HELIUM_ASSETS})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR}/Assets FILES ${HELIUM_ASSETS} PREFIX Assets)
ENDIF()

add_subdirectory(tools/HeliumCodeAssist)


target_compile_options(Helium PUBLIC "/arch:AVX2" "/MP")
target_compile_options(Helium PUBLIC
    "$<$<CONFIG:RELEASE>:/Oi>"
    "$<$<CONFIG:RELEASE>:/Oy>"
    "$<$<CONFIG:RELEASE>:/GL>"
    "$<$<CONFIG:RELEASE>:/GT>"
    "$<$<CONFIG:RELEASE>:/guard:cf>"
    "$<$<CONFIG:RELEASE>:/Gy>"
    "$<$<CONFIG:RELEASE>:/Qpar>"
)

target_link_options(Helium PUBLIC
    "$<$<CONFIG:RELEASE>:/LTCG:incremental>"
)