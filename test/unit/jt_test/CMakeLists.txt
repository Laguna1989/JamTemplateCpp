if (ENABLE_UNITTESTS)
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


    # Download and unpack googletest at configure time
    configure_file(${CMAKE_SOURCE_DIR}/ext/googletest/CMakeLists.txt.in ${CMAKE_BINARY_DIR}/ext/googletest/googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/ext/googletest/googletest-download)
    if (result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/ext/googletest/googletest-download)
    if (result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif ()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_BINARY_DIR}/ext/googletest/googletest-src
            ${CMAKE_BINARY_DIR}/ext/googletest/googletest-build
            EXCLUDE_FROM_ALL)

    add_executable(jt_tests ${UNITTESTFILES})
    if (ENABLE_WEB)
        set(CMAKE_EXECUTABLE_SUFFIX ".html")
    endif ()
    target_link_libraries(jt_tests gtest)
    target_link_libraries(jt_tests gmock)
    target_link_libraries(jt_tests JamTemplate)

    jt_use_assets(jt_tests)
    jt_deploy_dlls()
    add_test(jt_tests jt_tests)
endif ()
