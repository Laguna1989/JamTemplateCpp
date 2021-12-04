file(GLOB_RECURSE JAMTEMPLATEBASEFILES ${CMAKE_CURRENT_SOURCE_DIR}/common/*)
if (USE_SFML)
    file(GLOB_RECURSE JAMTEMPLATEFILES ${CMAKE_CURRENT_SOURCE_DIR}/sfml/*)
else ()
    file(GLOB_RECURSE JAMTEMPLATEFILES ${CMAKE_CURRENT_SOURCE_DIR}/sdl/*)
endif ()

add_library(JamTemplate ${JAMTEMPLATEFILES} ${JAMTEMPLATEBASEFILES})

# add public includes, so they can be used by dependent targets
target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)
target_include_directories(JamTemplate SYSTEM PUBLIC ${tileson_SOURCE_DIR}/include)
if (USE_SFML)
    target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sfml)
    target_include_directories(JamTemplate SYSTEM PUBLIC ${SFML_DIR_ROOT}/include)

    target_link_libraries(JamTemplate
            sfml-system
            sfml-window
            sfml-graphics
            sfml-audio
            )

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

FetchContent_GetProperties(range-v3)

add_library(range_v3 INTERFACE IMPORTED)
set_target_properties(range_v3 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${range-v3_SOURCE_DIR}/include)
target_link_libraries(JamTemplate range_v3)



