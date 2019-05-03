# ------------------------------------------------------------------------------
# File: CMakeLists.txt
# Created by Spark on 28/04/2019.
# ------------------------------------------------------------------------------

create_property(P_SHARED_LIBRARIES "")
create_property(P_STATIC_LIBRARIES "")
create_property(P_INTERFACE_LIBRARIES "")

# ------------------------------------------------------------------------------
# Coverage target (interface library)
# ------------------------------------------------------------------------------
add_library(coverage_config INTERFACE)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
    # Add required flags (GCC & LLVM/Clang)
    target_compile_options(coverage_config INTERFACE
            -O0        # no optimization
            -g         # generate debug info
            --coverage # sets all required flags
            )
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
        target_link_options(coverage_config INTERFACE --coverage)
    else()
        target_link_libraries(coverage_config INTERFACE --coverage)
    endif()
endif(ENABLE_COVERAGE)

# ------------------------------------------------------------------------------
# Warnings target (interface library)
# ------------------------------------------------------------------------------
add_library(warnings_config INTERFACE)

if(MSVC)
    target_compile_options(warnings_config INTERFACE /W4)
else()
    #target_compile_options(warnings_config INTERFACE -Wall -std=c++14)
    target_compile_options(warnings_config INTERFACE -Wall -Wextra -Wpedantic -std=c++14)
endif()

# ------------------------------------------------------------------------------
# ExternalProject & Git
# ------------------------------------------------------------------------------
# include(ExternalProject)
# find_package(Git REQUIRED)

# ------------------------------------------------------------------------------
#
# PUT DYNAMIC LIBRARIES HERE
#
# ------------------------------------------------------------------------------
if(NOT MSVC)
    set(BUILD_SHARED_LIBS ON)
endif()
set(BUILD_SHARED_LIBS_STATUS ${BUILD_SHARED_LIBS}) # Save BUILD_SHARED_LIBS value to prevent altering it in this file

# ------------------------------------------------------------------------------
# GoogleTest / GoogleMock
# ------------------------------------------------------------------------------
set(INSTALL_GMOCK ON)
set(INSTALL_GTEST ON)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)
if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)
add_subdirectory(googletest)
AddLibraryToProject(gtest)
AddLibraryToProject(gtest_main)
AddLibraryToProject(gmock)
AddLibraryToProject(gmock_main)

# ------------------------------------------------------------------------------
# CPPFS (Cross-Platform & Portable FileSystem library)
# ------------------------------------------------------------------------------
add_subdirectory(cppfs)
AddLibraryToProject(cppfs)

# ------------------------------------------------------------------------------
# LuaJIT 2.0.1
# ------------------------------------------------------------------------------
set(BUILD_LUAJIT ON)
if(BUILD_LUAJIT)
    add_subdirectory(luajit_2.0.3)
    AddLibraryToProject(liblua)
    target_include_directories(liblua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/luajit_2.0.3/src)
endif()

# ------------------------------------------------------------------------------
#
# PUT STATIC LIBRARIES HERE
#
# ------------------------------------------------------------------------------
set(BUILD_SHARED_LIBS OFF)

# ------------------------------------------------------------------------------
# Google Sanitizers
# ------------------------------------------------------------------------------
if(ENABLE_ASAN) # Address sanitizer
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
endif()

if(ENABLE_USAN) # Undefined sanitizer
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

if(ENABLE_TSAN) # Thread sanitizer
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
endif()

# ------------------------------------------------------------------------------
# Valgrind
# ------------------------------------------------------------------------------
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --track-fds=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")

set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_STATUS}) # Reset the BUILD_SHARED_LIBS value to what it was before