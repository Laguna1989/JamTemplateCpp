include(FetchContent)
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        GIT_TAG v1.6.0
)
FetchContent_MakeAvailable(googlebenchmark)

file(GLOB_RECURSE PERFORMANCEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(jt_performance ${PERFORMANCEFILES})

target_link_libraries(jt_performance benchmark::benchmark)
target_link_libraries(jt_performance JamTemplateLib)

if (NOT USE_SFML)
    if (WIN32)
        target_link_libraries(jt_performance SDL2::SDL2main)
        deploy_sdl_dlls()
    endif ()
endif ()

if (MSVC)
    target_compile_options(jt_performance PRIVATE "/W3")
    target_compile_options(jt_performance PRIVATE "/EHsc")
else ()
    target_compile_options(jt_performance PRIVATE "-Wall")
    target_compile_options(jt_performance PRIVATE "-Wextra")
endif ()

jt_use_assets(jt_performance)
