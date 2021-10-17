include(FetchContent)
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        )
FetchContent_MakeAvailable(googlebenchmark)


file(GLOB_RECURSE DEMOFILES ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(jt_performance ${DEMOFILES})

target_link_libraries(jt_performance benchmark::benchmark)
