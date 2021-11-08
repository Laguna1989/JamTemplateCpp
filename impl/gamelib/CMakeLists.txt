file(GLOB_RECURSE GAMELIBFILES ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_library(GameLib ${GAMELIBFILES} )
if (ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

target_link_libraries(GameLib PUBLIC JamTemplate)
target_include_directories(GameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

