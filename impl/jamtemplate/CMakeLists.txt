file(GLOB_RECURSE JAMTEMPLATEBASEFILES ${CMAKE_CURRENT_SOURCE_DIR}/common/*)
if (USE_SFML)
    file(GLOB_RECURSE JAMTEMPLATEFILES ${CMAKE_CURRENT_SOURCE_DIR}/sfml/*)
else ()
    file(GLOB_RECURSE JAMTEMPLATEFILES ${CMAKE_CURRENT_SOURCE_DIR}/sdl/*)
endif ()

add_library(JamTemplate ${JAMTEMPLATEFILES} ${JAMTEMPLATEBASEFILES})

FetchContent_GetProperties(tileson)

# add public includes, so they can be used by dependent targets
target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)
target_include_directories(JamTemplate SYSTEM PUBLIC ${tileson_SOURCE_DIR}/include)
if (USE_SFML)
    target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sfml)
    target_include_directories(JamTemplate SYSTEM PUBLIC ${SFML_DIR_ROOT}/include)

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

else ()
    target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sdl)
    if (NOT ENABLE_WEB)
        include_directories(JamTemplate ${SDL2_INCLUDE_DIRS})

        target_link_libraries(JamTemplate ${SDL2_LIBRARIES})
        target_link_libraries(JamTemplate PkgConfig::SDL2_Mixer)
        target_link_libraries(JamTemplate PkgConfig::SDL2_Image)
        target_link_libraries(JamTemplate PkgConfig::SDL2_TTF)

    endif ()
endif ()

target_link_libraries(JamTemplate Box2D)
