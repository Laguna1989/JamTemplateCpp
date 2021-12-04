message(STATUS "Add FetchContent")
include(FetchContent)

message(STATUS "Fetching external libraries started")

if (USE_SFML)
    add_subdirectory(sfml)
endif ()
add_subdirectory(tileson)
add_subdirectory(range-v3)
add_subdirectory(box2d)
#add_subdirectory(imgui)
#add_subdirectory(imgui-sfml)

message(STATUS "Fetching external libraries done")
