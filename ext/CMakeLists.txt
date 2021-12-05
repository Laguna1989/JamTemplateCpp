message(STATUS "Add FetchContent")
include(FetchContent)

message(STATUS "Fetching external libraries started")

add_subdirectory(range-v3)
add_subdirectory(box2d)
add_subdirectory(imgui)
if (USE_SFML)
    add_subdirectory(sfml)
    add_subdirectory(imgui-sfml)
else()
    add_subdirectory(imgui-sdl)
endif ()

add_subdirectory(tileson)


message(STATUS "Fetching external libraries done")
