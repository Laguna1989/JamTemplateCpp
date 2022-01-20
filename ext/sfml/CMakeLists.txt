message(STATUS "Fetching sfml")
FetchContent_Declare(
        SFML
        URL "https://github.com/SFML/SFML/archive/2.5.1.zip"
)

FetchContent_GetProperties(SFML)

if (NOT SFML_POPULATED)
    FetchContent_Populate(SFML)

    set(SFML_INSTALL_PKGCONFIG_FILES OFF)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_BUILD_AUDIO OFF)

    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
