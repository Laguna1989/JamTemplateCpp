message(STATUS "Fetching sdl2-ttf")
cmake_policy(SET CMP0135 OLD)
FetchContent_Declare(
sdl2-ttf
URL "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-devel-2.20.2-VC.zip"
)

FetchContent_GetProperties(sdl2-ttf)

if (NOT sdl2-ttf_POPULATED)
FetchContent_Populate(sdl2-ttf)
endif ()
