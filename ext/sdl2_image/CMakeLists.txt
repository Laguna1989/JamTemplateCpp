message(STATUS "Fetching sdl2-image")
cmake_policy(SET CMP0135 OLD)
FetchContent_Declare(
        sdl2-image
        URL "https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-devel-2.6.3-VC.zip"
)

FetchContent_GetProperties(sdl2-image)

if (NOT sdl2-image_POPULATED)
    FetchContent_Populate(sdl2-image)
endif ()
