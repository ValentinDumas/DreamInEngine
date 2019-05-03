project(DreamInEngine C CXX)

create_property(P_PROJECT_SOURCE_MODULES "")

# ------------------------------------------------------------------------------
# Project Modules / Libraries
# ------------------------------------------------------------------------------
add_subdirectory(utils)
add_subdirectory(mathematics)

# ------------------------------------------------------------------------------
# Main Target Executable
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} utils mathematics) # Note: pthread not needed !

MoveNeededResourcesToTarget(${PROJECT_NAME})
