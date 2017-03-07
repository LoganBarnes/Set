cmake_minimum_required ( VERSION 3.2.0 )
project ( Set )

option( BUILD_TESTS OFF "Build unit tests created with gmock/gtest framework" )

# namespace used for project
set ( PROJECT_NAMESPACE set )

# The version number.
set ( PROJECT_VERSION_MAJOR 1 )
set ( PROJECT_VERSION_MINOR 0 )
set ( PROJECT_VERSION_PATCH 0 )

# required before DefaultProjectLibrary.cmake
set( SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )

# other paths
set( SHARED_PATH ${PROJECT_SOURCE_DIR}/shared )
set( RES_PATH    ${PROJECT_SOURCE_DIR}/res    )
set( SHADER_PATH ${SHARED_PATH}/shaders       )

set( MODEL_PATH  ${PROJECT_SOURCE_DIR}/run/models )
set( INPUT_PATH  ${PROJECT_SOURCE_DIR}/run/input  )
set( OUTPUT_PATH ${PROJECT_SOURCE_DIR}/run/output )

set( PROJECT_CONFIG_FILE ${SHARED_PATH}/src/common/ProjectConfig.hpp.in )


set( USE_GLFW  ON CACHE BOOL "" FORCE )
set( USE_GLM   ON CACHE BOOL "" FORCE )
set( USE_GUI   ON CACHE BOOL "" FORCE )

set( USE_GMOCK ${BUILD_TESTS} CACHE BOOL "" FORCE )


# set variables from shared simulation project
add_subdirectory( ${SHARED_PATH} )



# header dirs
set(
    PROJECT_INCLUDE_DIRS

    ${SRC_DIR}/io
    ${SRC_DIR}/scene
    ${SRC_DIR}/relations
    )

# cpp files
set(
    PROJECT_SOURCE

    # ignored by compilers but added to project files
    ${SHARED_UNCRUSTIFY_FILE}
    ${SHADER_PATH}/default/shader.vert
    ${SHADER_PATH}/default/shader.frag

    ${SRC_DIR}/io/SetIOHandler.cpp
    ${SRC_DIR}/io/SetCallback.cpp

#    ${SRC_DIR}/relations/Geometry.cpp
    ${SRC_DIR}/relations/Relation.hpp

    ${SRC_DIR}/scene/Environment.cpp
    ${SRC_DIR}/scene/Scene.cpp
    )


set(
    TESTING_SOURCE
    ${SRC_DIR}/testing/RelationUnitTests.cpp
    )

set(
    TESTING_LINK_LIBS
    ${GMOCK_BOTH_LIBS}
    ${SHARED_LINK_LIBS}
    )

set(
    TESTING_DEP_TARGETS
    ${GMOCK_BOTH_LIBS}
    )

set(
    TESTING_SYSTEM_INCLUDE_DIRS
    ${GMOCK_INCLUDE_DIRS}
    ${SRC_DIR}/renderers/gpu/cuda
    )

set(
    TESTING_INCLUDE_DIRS
    ${SRC_DIR}/relations
    ${SRC_DIR}/testing
    )


# file with main function
set( PROJECT_MAIN ${SRC_DIR}/exec/Set.cpp )

#set_property ( GLOBAL PROPERTY CXX_STANDARD 14  )
include( ${SHARED_PATH}/cmake/DefaultProjectLibrary.cmake )

