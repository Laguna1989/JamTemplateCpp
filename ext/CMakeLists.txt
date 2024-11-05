message(STATUS "Add FetchContent")
include(FetchContent)

message(STATUS "Add CPM.cmake")
# download CPM.cmake
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.6/CPM.cmake
        ${CMAKE_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=11c3fa5f1ba14f15d31c2fb63dbc8628ee133d81c8d764caad9a8db9e0bacb07
)
include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)

message(STATUS "Fetching external libraries started")

CPMAddPackage(
        NAME api
        GITHUB_REPOSITORY Laguna1989/arbitrary_precision_int_cpp
        GIT_TAG master
        OPTIONS
        "API_ENABLE_UNIT_TESTS OFF"
        "API_ENABLE_PERFORMANCE_TESTS OFF"
)

CPMAddPackage(
        NAME tracy
        GITHUB_REPOSITORY wolfpld/tracy
        GIT_TAG v0.11.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

CPMAddPackage(
        NAME aselib
        GITHUB_REPOSITORY Laguna1989/aselib
        GIT_TAG v0.3.1
        OPTIONS
        "ASE_LIB_ENABLE_UNIT_TESTS OFF"
)

CPMAddPackage(
        NAME tileson
        GITHUB_REPOSITORY SSBMTonberry/tileson
        GIT_TAG v1.4.0
        OPTIONS
        "BUILD_TESTS OFF"
)

add_subdirectory(imgui)
add_subdirectory(box2d)

if (USE_SFML)
    add_subdirectory(sfml)
    add_subdirectory(imgui-sfml)
else ()
    if (WIN32)
        add_subdirectory(sdl2)
        add_subdirectory(sdl2_image)
        add_subdirectory(sdl2_ttf)
    endif ()
    add_subdirectory(imgui-sdl)
endif ()

if (JT_ENABLE_UNITTESTS)
    CPMAddPackage(
            NAME googletest
            GITHUB_REPOSITORY google/googletest
            GIT_TAG v1.14.0
            VERSION 1.14.0
            OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
    )
endif ()

message(STATUS "Fetching external libraries done")
