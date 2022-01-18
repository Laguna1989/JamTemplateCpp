message(STATUS "Fetching openalpp")
FetchContent_Declare(
        openalpp
        GIT_REPOSITORY https://github.com/Laguna1989/OpenALpp.git
        GIT_TAG master
)

set(OALPP_ENABLE_UNIT_TESTS OFF)
set(OALPP_ENABLE_INTEGRATION_TESTS OFF)

FetchContent_MakeAvailable(openalpp)
