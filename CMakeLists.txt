cmake_minimum_required(VERSION 3.20.0)

project(Helium VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# print architecture
message(STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")

add_executable(Helium)

find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(EASTL CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(argparse REQUIRED)

target_compile_definitions(
        Helium
        PRIVATE
        BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
        heliumDebug
        BOOST_STACKTRACE_USE_ADDR2LINE
)

target_compile_options(Helium PRIVATE -g -ggdb -fno-pie)

target_include_directories(Helium PRIVATE
    ${Boost_INCLUDE_DIRS})

# mono
message(STATUS "Mono found: $ENV{MONO_DIR}")
set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:$ENV{MONO_DIR}/lib/pkgconfig")

target_include_directories(Helium PRIVATE
        $ENV{MONO_DIR}/include/mono-2.0)

message(STATUS "PKG_CONFIG_PATH: $ENV{PKG_CONFIG_PATH}")
execute_process(COMMAND pkg-config --cflags monosgen-2 OUTPUT_VARIABLE MONO_CFLAGS)
execute_process(COMMAND pkg-config --libs monosgen-2 OUTPUT_VARIABLE MONO_LIBS)
# remove trailing whitespace
string(STRIP ${MONO_CFLAGS} MONO_CFLAGS)
string(STRIP ${MONO_LIBS} MONO_LIBS)
target_compile_options(Helium PRIVATE ${MONO_CFLAGS})
target_link_libraries(Helium PRIVATE ${MONO_LIBS})
#target_link_libraries(Helium PRIVATE $ENV{MONO_DIR}/lib/libmono-native-compat.dylib)
message(STATUS "MONO_CFLAGS: ${MONO_CFLAGS}")
message(STATUS "MONO_LIBS: ${MONO_LIBS}")

target_link_libraries(Helium PRIVATE fmt::fmt
    glad::glad
    glfw
    imgui::imgui
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

target_link_options(Helium PRIVATE -rdynamic)

target_link_libraries(Helium PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

# find all headers and source files
file(GLOB_RECURSE HELIUM_HEADERS CONFIGURE_DEPENDS src/Helium/*.h)
file(GLOB_RECURSE HELIUM_SOURCES CONFIGURE_DEPENDS src/Helium/*.cpp)

# pch
target_precompile_headers(Helium PRIVATE src/Helium/HeliumPrecompiled.h)

target_include_directories(Helium PRIVATE
    src
)

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

# add imgui backend include dir
target_include_directories(Helium PRIVATE
    ${imgui_DIR}/../../../imgui/backends
)

target_sources(Helium PRIVATE
    ${HELIUM_HEADERS}
    ${HELIUM_SOURCES}
)

