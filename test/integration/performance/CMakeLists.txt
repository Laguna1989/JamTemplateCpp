include(FetchContent)
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        GIT_TAG v1.6.0
        )
FetchContent_MakeAvailable(googlebenchmark)

file(GLOB_RECURSE PERFORMANCEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(jt_performance ${PERFORMANCEFILES})

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(jt_performance PUBLIC "SHELL:--use-preload-plugins")
    target_link_options(jt_performance PUBLIC --preload-file assets)
    target_link_options(jt_performance PRIVATE "SHELL:-s TOTAL_MEMORY=256MB")
    target_link_options(jt_performance PRIVATE "SHELL:-s ALLOW_MEMORY_GROWTH=1")
endif ()

target_link_libraries(jt_performance benchmark::benchmark)
target_link_libraries(jt_performance JamTemplateLib)

jt_use_assets(jt_performance)
