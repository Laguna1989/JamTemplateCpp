file(GLOB_RECURSE UNITTESTFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
if ((NOT JT_ENABLE_AUDIO_TESTS) OR JT_ENABLE_WEB)
    list(REMOVE_ITEM UNITTESTFILES
            "${CMAKE_CURRENT_SOURCE_DIR}/sound_test.cpp")
endif ()
if (NOT USE_SFML)
    list(REMOVE_ITEM UNITTESTFILES
            "${CMAKE_CURRENT_SOURCE_DIR}/game_test.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/render_window_sfml_test.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/sprite_sfml_test.cpp")
else ()
endif ()


add_executable(jt_tests ${UNITTESTFILES})
if (JT_ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

target_link_libraries(jt_tests
        gtest
        gmock_main
        JamTemplate
        )

jt_use_assets(jt_tests)
add_test(jt_tests jt_tests)
