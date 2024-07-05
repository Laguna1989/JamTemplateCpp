file(GLOB GAMEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_executable(${PROJECTNAME} ${GAMEFILES})
if (JT_ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

target_link_libraries(${PROJECTNAME} PUBLIC GameLib)
target_include_directories(${PROJECTNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (NOT USE_SFML)
    if (NOT JT_ENABLE_WEB)
        if (WIN32)
            target_link_libraries(${PROJECTNAME} PUBLIC SDL2::SDL2main)
            deploy_sdl_dlls()
        endif ()
    endif ()
endif ()

if (MSVC)
    target_compile_options(${PROJECTNAME} PRIVATE "/W3")
    target_compile_options(${PROJECTNAME} PRIVATE "/EHsc")
else ()
    target_compile_options(${PROJECTNAME} PRIVATE "-Wall")
    target_compile_options(${PROJECTNAME} PRIVATE "-Wextra")
endif ()

jt_link_fmod(${PROJECTNAME})


jt_use_assets(${PROJECTNAME})
