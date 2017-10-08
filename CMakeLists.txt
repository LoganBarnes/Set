cmake_minimum_required(VERSION 3.7)
project(AirWaves)

set(CMAKE_CXX_STANDARD 14)

option(SET_BUILD_TESTS OFF "Build unit tests created with the GTest framework")

include(cmake/DownloadProject.cmake)

# Download and unpack simulation driver at configure time
download_project(PROJ sim
        PREFIX thirdparty
        GIT_REPOSITORY https://github.com/LoganBarnes/SimulationDriver.git
        GIT_TAG master
        UPDATE_DISCONNECTED 0
        QUIET
        )

set(SIM_BUILD_CUDA OFF CACHE BOOL "" FORCE)
set(SIM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SIM_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# compile with current project
add_subdirectory(${sim_SOURCE_DIR} ${sim_BINARY_DIR})

# Download and unpack simulation driver at configure time
download_project(PROJ variant
        PREFIX thirdparty
        GIT_REPOSITORY https://github.com/mapbox/variant.git
        GIT_TAG master
        UPDATE_DISCONNECTED 0
        QUIET
        )

set(SOURCE_FILES
        src/set/Relation.hpp
        src/set/Scene.cpp
        src/set/Scene.hpp
        )

add_library(set ${SOURCE_FILES})
target_include_directories(set PUBLIC src)
target_include_directories(set SYSTEM PUBLIC ${variant_SOURCE_DIR}/include)
target_link_libraries(set SimDriver)

add_executable(set-exec src/exec/Set.cpp)
target_link_libraries(set-exec set)

if (${SET_BUILD_TESTS})
    # Download and unpack googletest at configure time
    download_project(PROJ gtest
            PREFIX thirdparty
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.8.0
            UPDATE_DISCONNECTED 1
            ${QUIET_FLAG}
            )

    # compile googletest with current project
    add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR})

    set(TEST_SOURCE_FILES
            src/testing/RelationUnitTests.cpp
            src/testing/TestingUtils.cpp src/testing/TestingUtils.hpp)

    add_executable(set-tests ${TEST_SOURCE_FILES})
    add_test(NAME empty-test COMMAND set-tests)
    target_link_libraries(set-tests set gtest_main)
endif ()
