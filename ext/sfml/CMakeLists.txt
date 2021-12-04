message(STATUS "Fetching sfml")
FetchContent_Declare(
        SFML
        URL "https://github.com/SFML/SFML/archive/2.5.1.zip"
)

FetchContent_GetProperties(SFML)

if (NOT SFML_POPULATED)
    set(SFML_INSTALL_PKGCONFIG_FILES OFF CACHE BOOL "Install pkgconfig files")

    FetchContent_Populate(SFML)

    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
