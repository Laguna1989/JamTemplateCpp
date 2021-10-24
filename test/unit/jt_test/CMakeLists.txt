file(GLOB_RECURSE UNITTESTFILES ${CMAKE_CURRENT_SOURCE_DIR}/*)
if ((NOT ENABLE_AUDIO_TESTS) OR ENABLE_WEB)
    list(REMOVE_ITEM UNITTESTFILES
            "${CMAKE_CURRENT_SOURCE_DIR}/sound_test.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/music_player_test.cpp")
endif ()
if (NOT USE_SFML)
    list(REMOVE_ITEM UNITTESTFILES
            "${CMAKE_CURRENT_SOURCE_DIR}/game_test.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/game_sfml_test.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/render_window_sfml_test.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/sprite_sfml_test.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/vector_sfml_test.cpp")
else ()
    list(REMOVE_ITEM UNITTESTFILES
            "${CMAKE_CURRENT_SOURCE_DIR}/vector_sdl_test.cpp")
endif ()


add_executable(jt_tests ${UNITTESTFILES})
if (ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()
target_link_libraries_system(jt_tests gtest)
target_link_libraries_system(jt_tests gmock)
target_link_libraries(jt_tests JamTemplate)

jt_use_assets(jt_tests)
jt_deploy_dlls()
add_test(jt_tests jt_tests)
