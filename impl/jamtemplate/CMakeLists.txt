file(GLOB_RECURSE JAMTEMPLATEBASEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/common/*)
if (USE_SFML)
    file(GLOB_RECURSE JAMTEMPLATEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/sfml/*)
else ()
    file(GLOB_RECURSE JAMTEMPLATEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/sdl/*)
endif ()

execute_process(
        COMMAND git rev-parse -q HEAD
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        RESULT_VARIABLE res
        OUTPUT_VARIABLE GIT_SHA1
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

string(TIMESTAMP CONFIGURE_TIMESTAMP "%Y-%m-%d %H:%M:%S")

configure_file("${CMAKE_SOURCE_DIR}/config/git_version.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/git_version.cpp" @ONLY)
list(APPEND JAMTEMPLATEBASEFILES "${CMAKE_CURRENT_BINARY_DIR}/git_version.cpp")

add_library(JamTemplate STATIC ${JAMTEMPLATEFILES} ${JAMTEMPLATEBASEFILES})

# add public includes, so they can be used by dependent targets
target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)
target_include_directories(JamTemplate SYSTEM PUBLIC ${tileson_SOURCE_DIR}/include)

FetchContent_GetProperties(tileson)
FetchContent_GetProperties(openalpp)
target_include_directories(JamTemplate PUBLIC ${tileson_SOURCE_DIR}/extras/)

target_link_libraries(JamTemplate
        OpenALpp_Lib
        Box2D
        )


if (USE_SFML)
    target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sfml)
    target_include_directories(JamTemplate SYSTEM PUBLIC ${SFML_DIR_ROOT}/include)

    target_link_libraries(JamTemplate
            sfml-system
            sfml-window
            sfml-graphics
            ImGui-SFML::ImGui-SFML
            )

else ()
    target_link_libraries(JamTemplate
            imgui-sdl
            )

    target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sdl)
    if (NOT JT_ENABLE_WEB)
        include_directories(JamTemplate ${SDL2_INCLUDE_DIRS})

        target_link_libraries(JamTemplate
                ${SDL2_LIBRARIES}
                PkgConfig::SDL2_Image
                PkgConfig::SDL2_TTF
                )
    endif ()
endif ()



