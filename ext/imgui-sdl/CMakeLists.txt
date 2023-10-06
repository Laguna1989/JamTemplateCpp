message(STATUS "Fetching imgui-sdl")

if (JT_ENABLE_WEB OR NOT WIN32)
    FetchContent_Declare(
            imgui-sdl
            GIT_REPOSITORY https://github.com/Laguna1989/imgui_sdl.git
            GIT_TAG WebAssemblyInclude
    )
else()
    FetchContent_Declare(
            imgui-sdl
            GIT_REPOSITORY https://github.com/Laguna1989/imgui_sdl.git
            GIT_TAG master
    )
endif()

FetchContent_Populate(imgui-sdl)
FetchContent_GetProperties(imgui-sdl)

# imgui is supposed to be added to the project files. Lets keep it in the imgui-sdl project for now
FetchContent_GetProperties(imgui)
file(GLOB IMGUIHEADERS ${imgui_SOURCE_DIR}/*.h)
file(GLOB IMGUISOURCES ${imgui_SOURCE_DIR}/*.cpp)


add_library(imgui-sdl STATIC ${IMGUIHEADERS} ${IMGUISOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_sdl.h ${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_sdl.cpp ${imgui-sdl_SOURCE_DIR}/imgui_sdl.h ${imgui-sdl_SOURCE_DIR}/imgui_sdl.cpp)
target_include_directories(imgui-sdl SYSTEM PUBLIC ${imgui_SOURCE_DIR}/)
target_include_directories(imgui-sdl SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
target_include_directories(imgui-sdl SYSTEM PUBLIC ${imgui-sdl_SOURCE_DIR}/)

if (JT_ENABLE_WEB)
    target_link_libraries(imgui-sdl ${SDL2_LIBRARIES} )
else()
    if (WIN32)
        FetchContent_GetProperties(sdl2)
        set(SDL2_DIR "${sdl2_SOURCE_DIR}/cmake" CACHE PATH "Path to sdl2 root dir.")
        find_package(SDL2 REQUIRED)
        target_link_libraries(imgui-sdl SDL2::SDL2 )
    endif()
endif()
