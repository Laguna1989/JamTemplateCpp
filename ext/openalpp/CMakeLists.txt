message(STATUS "Fetching openalpp")
FetchContent_Declare(
        openalpp
        GIT_REPOSITORY https://github.com/Laguna1989/OpenALpp.git
        GIT_TAG master
)

FetchContent_MakeAvailable(openalpp)
