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
find_package(yaml-cpp CONFIG REQUIRED)
find_package(EASTL CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(argparse REQUIRED)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/imgui)

target_compile_definitions(
        Helium
        PUBLIC
        BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
        heliumDebug
        BOOST_STACKTRACE_USE_ADDR2LINE
)

target_compile_options(Helium PUBLIC -g -ggdb -fno-pie)

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

target_link_options(Helium PUBLIC -rdynamic)

target_link_libraries(Helium PUBLIC spdlog::spdlog spdlog::spdlog_header_only)

# find all headers and source files
file(GLOB_RECURSE HELIUM_HEADERS CONFIGURE_DEPENDS src/Helium/*.h)
file(GLOB_RECURSE HELIUM_SOURCES CONFIGURE_DEPENDS src/Helium/*.cpp)

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

IF(WIN32)
foreach(FILE ${HELIUM_SOURCES})
  get_filename_component(PARENT_DIR "${FILE}" PATH)

  file(RELATIVE_PATH PARENT_DIR_RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${PARENT_DIR})

  string(REPLACE "/" "\\" GROUP "${PARENT_DIR_RELATIVE}")

  set(GROUP "File Tree\\${GROUP}")

  source_group("${GROUP}" FILES "${FILE}")
endforeach()

foreach(FILE ${HELIUM_HEADERS})
  get_filename_component(PARENT_DIR "${FILE}" PATH)

  file(RELATIVE_PATH PARENT_DIR_RELATIVE ${CMAKE_CURRENT_LIST_DIR}  ${PARENT_DIR})

  string(REPLACE "/" "\\" GROUP "${PARENT_DIR_RELATIVE}")

  set(GROUP "File Tree\\${GROUP}")

  source_group("${GROUP}" FILES "${FILE}")
endforeach()
ENDIF()
