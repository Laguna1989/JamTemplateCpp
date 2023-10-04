message(STATUS "Fetching sdl2")
cmake_policy(SET CMP0135 OLD)
FetchContent_Declare(
sdl2
URL "https://github.com/libsdl-org/SDL/releases/download/release-2.28.4/SDL2-devel-2.28.4-VC.zip"
)

FetchContent_GetProperties(sdl2)

if (NOT sdl2_POPULATED)
    FetchContent_Populate(sdl2)
endif ()
