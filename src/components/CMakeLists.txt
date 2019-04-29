# ------------------------------------------------------------------------------
# File: CMakeLists.txt
# Created by Spark on 29/04/2019.
# ------------------------------------------------------------------------------

project(components)

# ------------------------------------------------------------------------------
# Target details
# ------------------------------------------------------------------------------
#TODO: Check if we can handle multiple source files while building with CI Tools (online)
set(${PROJECT_NAME}_SOURCE_FILES BoxPhysics.cpp ContactListener.cpp Input.cpp Shader.cpp Sprite.cpp Texture.cpp)
set(${PROJECT_NAME}_COVERAGE ON)
set(${PROJECT_NAME}_WARNINGS ON)

# ------------------------------------------------------------------------------
# Target library
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC "${${PROJECT_NAME}_SOURCE_FILES}" "${${PROJECT_NAME}_HEADER_FILES}")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(${PROJECT_NAME} PRIVATE glad utils Box2D glm coverage_config)

AddLibraryToProject(components)

#add_custom_library(STATIC ${PROJECT_NAME} "${${PROJECT_NAME}_SOURCE_FILES}" PUBLIC "${${PROJECT_NAME}_INCLUDE_DIRS}" "${${PROJECT_NAME}_LIBRARIES}" ${PROJECT_NAME}_COVERAGE ${PROJECT_NAME}_WARNINGS)