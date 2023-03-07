message(STATUS "Fetching api")
FetchContent_Declare(
        api
        GIT_REPOSITORY https://github.com/Laguna1989/arbitrary_precision_int_cpp.git
        GIT_TAG master
)

set(API_ENABLE_UNIT_TESTS OFF)
set(API_ENABLE_PERFORMANCE_TESTS OFF)
FetchContent_MakeAvailable(api)
