message(STATUS "Fetching asiocmake")
include(FetchContent)

# Download this repository
include(FetchContent)

option(ASIO_USE_CPM "Download Asio with CPM instead of FetchContent" OFF)
option(
        ASIO_CPM_FETCHCONTENT_COMPAT
        "Should asio be declared with FetchContent functions to be compatible. This doesn't not allow CPM cache to work."
        ON
)

FetchContent_Declare(
        asiocmake
        GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
        GIT_TAG        v1.2.0
)
FetchContent_MakeAvailable(asiocmake)
