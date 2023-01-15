message(STATUS "Fetching tileson")
FetchContent_Declare(
        tileson
        GIT_REPOSITORY https://github.com/SSBMTonberry/tileson.git
        GIT_TAG master
)

SET(BUILD_TESTS OFF)
FetchContent_GetProperties(tileson)

if (NOT tileson_POPULATED)
    FetchContent_Populate(tileson)

    add_subdirectory(${tileson_SOURCE_DIR} ${tileson_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
