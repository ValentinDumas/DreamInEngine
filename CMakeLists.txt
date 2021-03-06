# ------------------------------------------------------------------------------
# CMake version
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.2)

# ------------------------------------------------------------------------------
# Load tools and functions
# ------------------------------------------------------------------------------
add_subdirectory(tools)

# ------------------------------------------------------------------------------
# Project information
# ------------------------------------------------------------------------------
project(DreamInEngine C CXX)

# ------------------------------------------------------------------------------
# CMake build configuration: Debug or Release
# ------------------------------------------------------------------------------
# set(CMAKE_BUILD_TYPE Debug)
# message(CMAKE Build Type => ${CMAKE_BUILD_TYPE})

# -----------------------------------------------------------------------------
# Other CMake options
# ------------------------------------------------------------------------------
# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

if(APPLE)
    message("SFML: Apple building !")
    include_directories(externals/sfml_2.5.1/include)
    link_directories(${PROJECT_SOURCE_DIR}/externals/sfml_2.5.1/lib)
    add_definitions(-DCMAKE_MACOSX_RPATH=ON)
endif()

# Turn off shared libs to manage static/shared libraries
set(BUILD_SHARED_LIBS OFF)
if(MSVC)
    set(BUILD_SHARED_LIBS OFF) # force STATIC builds on MSVC
    add_definitions(-DMSVC_PLATFORM)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS")
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # enable it before using "clang tidy"

# Note: Can be OFF when testing (CI). Turn ON only to build an executable directly in project instead of CMake binary folder
set(BUILD_EXECUTABLE_IN_PROJECT_TREE OFF)

# ------------------------------------------------------------------------------
# Testing options
# ------------------------------------------------------------------------------
message("Tests are configured in STANDALONE mode")

# TODO: this code should be added to a specific target (function)
if(MINGW)
    #get_filename_component(c_compiler_dir ${CMAKE_C_COMPILER} PATH)
    get_filename_component(cxx_compiler_dir ${CMAKE_CXX_COMPILER} PATH)

    #message("${c_compiler_dir}")
    message("${cxx_compiler_dir}")

    #    if(NOT(EXISTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}))
    #        file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    #    endif()
    configure_file("${cxx_compiler_dir}/libgcc_s_seh-1.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COPYONLY)
    configure_file("${cxx_compiler_dir}/libstdc++-6.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COPYONLY)
    configure_file("${cxx_compiler_dir}/libwinpthread-1.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COPYONLY)
endif()

# ------------------------------------------------------------------------------
# Assets
# ------------------------------------------------------------------------------
#add_subdirectory(assets)

# ------------------------------------------------------------------------------
# External dependencies
# ------------------------------------------------------------------------------
set(BUILD_ASSIMP_LIBRARY OFF) # Note: set to ON to build the Assimp 3D Model Loader library
# set(BUILD_BULLET_LIBRARY OFF) # Note: set to ON to build the Bullet physics library
add_subdirectory(externals)

# ------------------------------------------------------------------------------
# Sources and modules
# ------------------------------------------------------------------------------
add_subdirectory(src)

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
option (BUILD_TESTING "Build the testing tree." ON)
# Only build tests if we are the top-level project
# Allows this to be used by super projects with `add_subdirectory`
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

# ------------------------------------------------------------------------------
# Examples
# ------------------------------------------------------------------------------
set(BUILD_EXAMPLES OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ------------------------------------------------------------------------------
# Debug information
# ------------------------------------------------------------------------------
get_property_by_name(SHARED_LIBRARIES P_SHARED_LIBRARIES)
get_property_by_name(STATIC_LIBRARIES P_STATIC_LIBRARIES)
get_property_by_name(INTERFACE_LIBRARIES P_INTERFACE_LIBRARIES)
message("SHARED LIBRARIES for the whole solution: ${SHARED_LIBRARIES}")
message("STATIC LIBRARIES for the whole solution: ${STATIC_LIBRARIES}")
message("INTERFACE LIBRARIES for the whole solution: ${INTERFACE_LIBRARIES}")
