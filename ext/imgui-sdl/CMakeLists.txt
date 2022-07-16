message(STATUS "Fetching imgui-sdl")

FetchContent_Declare(
        imgui-sdl
        GIT_REPOSITORY https://github.com/Laguna1989/imgui_sdl.git
        GIT_TAG WebAssemblyInclude
)

FetchContent_Populate(imgui-sdl)
FetchContent_GetProperties(imgui-sdl)

# imgui is supposed to be added to the project files. Lets keep it in the imgui-sdl project for now
FetchContent_GetProperties(imgui)
file(GLOB IMGUIHEADERS ${imgui_SOURCE_DIR}/*.h)
file(GLOB IMGUISOURCES ${imgui_SOURCE_DIR}/*.cpp)


add_library(imgui-sdl STATIC ${IMGUIHEADERS} ${IMGUISOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_sdl.h ${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_sdl.cpp ${imgui-sdl_SOURCE_DIR}/imgui_sdl.h ${imgui-sdl_SOURCE_DIR}/imgui_sdl.cpp)

target_compile_options(imgui-sdl PUBLIC -s USE_SDL=2)
target_compile_options(imgui-sdl PUBLIC -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"bmp\",\"png\"]')
target_compile_options(imgui-sdl PUBLIC -s USE_SDL_TTF=2)


target_include_directories(imgui-sdl SYSTEM PUBLIC ${imgui_SOURCE_DIR}/)
target_include_directories(imgui-sdl SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
target_include_directories(imgui-sdl SYSTEM PUBLIC ${imgui-sdl_SOURCE_DIR}/)

target_link_libraries(imgui-sdl ${SDL2_LIBRARIES} )
