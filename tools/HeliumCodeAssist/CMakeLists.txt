cmake_minimum_required(VERSION 3.20.0)

project(HeliumCodeAssist LANGUAGES CSharp)

file(GLOB_RECURSE ASSIST_SOURCES src/*)
file(GLOB_RECURSE MANAGED_CLASS_DECLARATION_SOURCES ${HELIUM_SOURCE_DIR}/*.declaration.cs)

add_executable(HeliumCodeAssist
    ${ASSIST_SOURCES}
    ${MANAGED_CLASS_DECLARATION_SOURCES}
)

target_compile_options(HeliumCodeAssist PRIVATE "/langversion:11")

