include(FetchContent)
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        GIT_TAG v1.6.0
        )
FetchContent_MakeAvailable(googlebenchmark)

file(GLOB_RECURSE PERFORMANCEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(jt_performance ${PERFORMANCEFILES})

target_link_libraries(jt_performance benchmark::benchmark)
target_link_libraries(jt_performance JamTemplate)

jt_use_assets(jt_performance)
