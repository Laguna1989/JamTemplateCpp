file(GLOB GAMELIBFILES ${CMAKE_CURRENT_SOURCE_DIR}/*)
file(GLOB HUDFILES ../gamelib/hud/*)

add_library(GameLib ${GAMELIBFILES} ${HUDFILES})
if (ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

target_link_libraries(GameLib PUBLIC JamTemplate)
target_include_directories(GameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

