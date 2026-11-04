message(STATUS "Fetching ImGui")

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.9b # imgui-sfml for SFML 2 does not support imgui >= 1.92
)

FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
endif ()

if (NOT USE_SFML)
    # For SDL, use the platform and renderer backends that ship with Dear ImGui.
    # (SFML uses imgui-sfml, which compiles the imgui sources itself.)
    file(GLOB IMGUIHEADERS ${imgui_SOURCE_DIR}/*.h)
    file(GLOB IMGUISOURCES ${imgui_SOURCE_DIR}/*.cpp)

    add_library(imgui-backend-sdl2 STATIC
            ${IMGUIHEADERS}
            ${IMGUISOURCES}
            ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
    )
    target_include_directories(imgui-backend-sdl2 SYSTEM PUBLIC ${imgui_SOURCE_DIR}/ ${imgui_SOURCE_DIR}/backends/)

    if (JT_ENABLE_WEB)
        target_link_libraries(imgui-backend-sdl2 ${SDL2_LIBRARIES})
    elseif (WIN32)
        FetchContent_GetProperties(sdl2)
        set(SDL2_DIR "${sdl2_SOURCE_DIR}/cmake" CACHE PATH "Path to sdl2 root dir.")
        find_package(SDL2 REQUIRED)
        target_link_libraries(imgui-backend-sdl2 SDL2::SDL2)
    else ()
        # The backends include "SDL.h" directly. setup_sdl() runs after ext/, so look SDL2 up here.
        find_package(SDL2 REQUIRED)
        target_include_directories(imgui-backend-sdl2 SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})
    endif ()
endif ()
