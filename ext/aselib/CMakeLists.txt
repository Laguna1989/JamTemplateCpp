message(STATUS "Fetching aselib")
FetchContent_Declare(
        aselib
        GIT_REPOSITORY https://github.com/Laguna1989/aselib.git
        GIT_TAG v0.1.0
)
set(ASE_LIB_ENABLE_UNIT_TESTS OFF)
FetchContent_MakeAvailable(aselib)
