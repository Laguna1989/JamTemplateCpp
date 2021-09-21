file(GLOB_RECURSE JAMTEMPLATEBASEFILES ${CMAKE_CURRENT_SOURCE_DIR}/common/*)
if (ENABLE_WEB)
    file(GLOB_RECURSE JAMTEMPLATEFILES ${CMAKE_CURRENT_SOURCE_DIR}/sdl/*)
else ()
    file(GLOB_RECURSE JAMTEMPLATEFILES ${CMAKE_CURRENT_SOURCE_DIR}/sfml/*)
endif ()

add_library(JamTemplate ${JAMTEMPLATEFILES} ${JAMTEMPLATEBASEFILES})

FetchContent_GetProperties(tileson)

# add public includes, so they can be used by dependent targets
target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)
target_include_directories(JamTemplate SYSTEM PUBLIC ${tileson_SOURCE_DIR}/include)
if (ENABLE_WEB)
    target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sdl)
else ()
    target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sfml)
    target_include_directories(JamTemplate SYSTEM PUBLIC ${SFML_DIR_ROOT}/include)
endif ()

if (NOT ENABLE_WEB)

    target_link_libraries(JamTemplate optimized sfml-system)
    target_link_libraries(JamTemplate optimized sfml-window)
    target_link_libraries(JamTemplate optimized sfml-graphics)
    target_link_libraries(JamTemplate optimized sfml-audio)

    if (WIN32)
        target_link_libraries(JamTemplate debug sfml-system-d)
        target_link_libraries(JamTemplate debug sfml-window-d)
        target_link_libraries(JamTemplate debug sfml-graphics-d)
        target_link_libraries(JamTemplate debug sfml-audio-d)
    endif ()
endif ()

target_link_libraries(JamTemplate Box2D)
