cmake_minimum_required(VERSION 3.19)
set(PROJECTNAME "MyAwesomeGame")
project(${PROJECTNAME})

## Helper Functions
#####################################################
include(config/cmake/helpers.cmake)
include(config/cmake/cache_variables.cmake)

set(SFML_STATIC_LIBRARIES TRUE)
set(BUILD_SHARED_LIBS OFF)

## Other variables and compiler setup I
#####################################################

if (JT_ENABLE_AUDIO_TESTS)
    add_definitions(-DJT_ENABLE_AUDIO_TESTS)
endif ()

if (JT_ENABLE_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
endif ()

if (JT_ENABLE_WEB)
    add_compile_definitions(MUSIC_OGG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O0 -g --std=c++17 -fpermissive ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --use-preload-plugins --preload-file assets")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"bmp\",\"png\"]'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL_MIXER=2 -s USE_VORBIS=1 -s USE_OGG=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL_TTF=2")

    add_link_options("SHELL:-s TOTAL_MEMORY=256MB " "SHELL:-s ALLOW_MEMORY_GROWTH=1")
else ()
    if (MSVC)
        ## nasty warning 5205 from tileson should not show up,
        ## so the warning level of this one is set to 4 and the global warning level is set to three
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w45205 /W3 /EHsc")
    else ()
        if (JT_ENABLE_COVERAGE)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -O0 -fprofile-arcs -ftest-coverage --std=c++17 -fpermissive -lstdc++fs")
        elseif (JT_ENABLE_PERFORMANCETESTS)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 --std=c++17 -fpermissive -lstdc++fs")
        else ()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 --std=c++17 -fpermissive -lstdc++fs")
        endif ()
    endif ()
endif ()


## get externals
#####################################################
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
add_subdirectory(ext)

## Other variables and compiler setup II
#####################################################
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD 17)


FetchContent_GetProperties(sfml)
# Apple users: set to /usr/local/Cellar/sfml/2.4.2_1/lib/ or respectively
if (WIN32)
    set(SFML_DIR_ROOT "${sfml_SOURCE_DIR}" CACHE PATH "Path to SFML root dir.")
endif ()

if ($ENV{CLION_IDE})
    set(SFML_DIR "${SFML_DIR_ROOT}/lib/cmake/SFML")
endif ()

#####################################################
## Set link directories
#####################################################

if (USE_SFML)
    if (WIN32 OR APPLE)
        link_directories(${SFML_DIR_ROOT}/lib)
    endif ()
else ()
    if (NOT JT_ENABLE_WEB)
        find_package(SDL2 REQUIRED)

        include(FindPkgConfig)
        pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
        pkg_check_modules(SDL2_Image REQUIRED IMPORTED_TARGET SDL2_image)
        pkg_check_modules(SDL2_TTF REQUIRED IMPORTED_TARGET SDL2_ttf)
    endif ()
endif ()


## setup Projects
#####################################################
add_subdirectory(impl)
add_subdirectory(test)

## copy .clang-format to build directory
#####################################################
configure_file(${CMAKE_SOURCE_DIR}/.clang-format ${CMAKE_BINARY_DIR}/ COPYONLY)
