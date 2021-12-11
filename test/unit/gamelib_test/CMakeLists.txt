file(GLOB_RECURSE GAMELIBUNITTESTFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_executable(gamelib_tests ${GAMELIBUNITTESTFILES})
if (JT_ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()
target_link_libraries_system(gamelib_tests gtest)
target_link_libraries_system(gamelib_tests gmock_main)
target_link_libraries_system(gamelib_tests GameLib)

jt_use_assets(gamelib_tests)
add_test(gamelib_tests gamelib_tests)
