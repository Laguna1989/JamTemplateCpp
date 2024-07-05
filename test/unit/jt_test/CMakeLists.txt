file(GLOB_RECURSE UNITTESTFILES_COMMON CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/common/*)
file(GLOB UNITTESTFILES_BASE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
file(GLOB_RECURSE UNITTESTFILES_SFML CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/sfml/*)
file(GLOB_RECURSE UNITTESTFILES_SDL CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/sdl/*)

set(UNITTESTFILES_ALL ${UNITTESTFILES_COMMON} ${UNITTESTFILES_BASE})

if (USE_SFML)
    list(APPEND UNITTESTFILES_ALL ${UNITTESTFILES_SFML})
else ()
    list(APPEND UNITTESTFILES_ALL ${UNITTESTFILES_SDL})
endif ()

if ((NOT JT_ENABLE_AUDIO_TESTS) OR JT_ENABLE_WEB)
    list(REMOVE_ITEM UNITTESTFILES_ALL
            "${CMAKE_CURRENT_SOURCE_DIR}/common/audio/sound_test.cpp")
endif ()


add_executable(jt_tests ${UNITTESTFILES_ALL})
if (JT_ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

if (NOT USE_SFML)
    if (WIN32)
        target_link_libraries(jt_tests SDL2::SDL2main)
        deploy_sdl_dlls()
    endif ()
endif ()

if (MSVC)
    target_compile_options(jt_tests PRIVATE "/W3")
    target_compile_options(jt_tests PRIVATE "/EHsc")
else ()
    target_compile_options(jt_tests PRIVATE "-Wall")
    target_compile_options(jt_tests PRIVATE "-Wextra")
endif ()


target_include_directories(jt_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(jt_tests
        gtest
        gmock_main
        JamTemplateLib
)

jt_use_assets(jt_tests)
add_test(jt_tests jt_tests)
