message(STATUS "Add FetchContent")
include(FetchContent)

message(STATUS "Add CPM.cmake")
# download CPM.cmake
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.43.2/CPM.cmake
        ${CMAKE_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=49a3bef91ceb65bb66d57255e12d1ffd22abc2f6408fa9fe4534c544a2f232aa
)
include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)

message(STATUS "Fetching external libraries started")

CPMAddPackage(
        NAME api
        GITHUB_REPOSITORY Laguna1989/arbitrary_precision_int_cpp
        GIT_TAG 41282f83437c6483e1da887bec3ee01880fd40b6 # head of master
        OPTIONS
        "API_ENABLE_UNIT_TESTS OFF"
        "API_ENABLE_PERFORMANCE_TESTS OFF"
)

CPMAddPackage(
        NAME tracy
        GITHUB_REPOSITORY wolfpld/tracy
        GIT_TAG v0.14.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

CPMAddPackage(
        NAME aselib
        GITHUB_REPOSITORY Laguna1989/aselib
        GIT_TAG v0.3.2
        OPTIONS
        "ASE_LIB_ENABLE_UNIT_TESTS OFF"
)

CPMAddPackage(
        NAME tileson
        GITHUB_REPOSITORY SSBMTonberry/tileson
        GIT_TAG v1.4.0
        PATCH_COMMAND ${CMAKE_COMMAND} -DTILESON_INCLUDE_DIR=<SOURCE_DIR>/include -P ${CMAKE_CURRENT_LIST_DIR}/../config/cmake/patch_tileson.cmake
        OPTIONS
        "BUILD_TESTS OFF"
)

add_subdirectory(box2d)

if (USE_SFML)
    add_subdirectory(sfml)
    add_subdirectory(imgui)
    add_subdirectory(imgui-sfml)
else ()
    if (WIN32)
        add_subdirectory(sdl2)
        add_subdirectory(sdl2_image)
        add_subdirectory(sdl2_ttf)
    endif ()
    add_subdirectory(imgui)
endif ()

if (JT_ENABLE_UNITTESTS)
    CPMAddPackage(
            NAME googletest
            GITHUB_REPOSITORY google/googletest
            GIT_TAG v1.18.0
            VERSION 1.18.0
            OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
    )
endif ()

message(STATUS "Fetching external libraries done")
