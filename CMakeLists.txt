cmake_minimum_required(VERSION 3.24)

project(jiel
    VERSION 0.1.0
    DESCRIPTION "A portable OpenGL application"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(JIEL_BUILD_APPS "Build applications" ON)
option(JIEL_ENABLE_WARNINGS "Enable compiler warnings" ON)
option(JIEL_ENABLE_SANITIZERS
       "Enable address and undefined behavior sanitizers" OFF)

include(cmake/CompilerWarnings.cmake)
include(cmake/Dependencies.cmake)

if(JIEL_ENABLE_SANITIZERS
   AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    add_compile_options(-g -O1 -fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

add_subdirectory(src)

if(JIEL_BUILD_APPS)
    add_subdirectory(apps)
endif()
