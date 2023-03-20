file(GLOB_RECURSE GAMELIBFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_library(GameLib STATIC ${GAMELIBFILES})
if (JT_ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

target_link_libraries(GameLib PUBLIC JamTemplateLib)
target_include_directories(GameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if (MSVC)
    target_compile_options(GameLib PRIVATE "/W3")
    target_compile_options(GameLib PRIVATE "/EHsc")
else ()
    target_compile_options(GameLib PRIVATE "-Wall")
    target_compile_options(GameLib PRIVATE "-Wextra")
endif ()

