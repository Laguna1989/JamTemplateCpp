FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml.git
        GIT_TAG v2.4
)

set(SFML_DIR ${SFML_DIR_ROOT})

FetchContent_GetProperties(imgui-sfml)

if (NOT imgui-sfml_POPULATED)
    message(STATUS "Fetching ImGui-SFML v${IMGUI_SFML_VERSION}")

    FetchContent_Populate(imgui-sfml)

    # Fetch ImGui if needed
    FetchContent_GetProperties(imgui)
    if (NOT imgui_POPULATED)
        FetchContent_Populate(imgui)
    endif ()

    # Set relevant vars
    set(IMGUI_DIR ${imgui_SOURCE_DIR})
    set(IMGUI_SFML_FIND_SFML CACHE BOOL OFF)
    set(IMGUI_SFML_IMGUI_DEMO CACHE BOOL ON)


    add_subdirectory(${imgui-sfml_SOURCE_DIR} ${imgui-sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
