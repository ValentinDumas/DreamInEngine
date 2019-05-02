# ------------------------------------------------------------------------------
# File: CMakeLists.txt
# Created by Spark on 28/04/2019.
# ------------------------------------------------------------------------------

project(DreamInEngine)

create_property(P_PROJECT_SOURCE_MODULES "")

# ------------------------------------------------------------------------------
# Project modules
# ------------------------------------------------------------------------------
# Note: Put all project modules that depends on the main project down below.
add_subdirectory(utils)
add_subdirectory(lua)
add_subdirectory(mathematics)
#add_subdirectory(components)

# ------------------------------------------------------------------------------
# Main target details
# ------------------------------------------------------------------------------
# TODO: create a variable CI_OPENGL_TEMPLATE_PROJECT_SOURCE_MODULES
set(${PROJECT_NAME}_SOURCE_FILES main.cpp) # TODO: remove ResourceManager.cpp ?
set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}) # by including this, we have access to all other submodules folders even from "examples" and "tests" folders
set(${PROJECT_NAME}_LIBRARIES imgui glfw glad glm stb Box2D sfml-system sfml-window sfml-network sfml-graphics sfml-audio stb utils lua mathematics) # TODO: imgui before "glfw" and "glad" ?
set(${PROJECT_NAME}_COVERAGE ON)
set(${PROJECT_NAME}_WARNINGS OFF)

# ------------------------------------------------------------------------------
# Main Target Executable
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_INCLUDE_DIRS) # Note: PRIVATE 'cause this is the main target

target_link_libraries(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_LIBRARIES}) # Note: pthread not needed !

MoveNeededResourcesToTarget(${PROJECT_NAME})