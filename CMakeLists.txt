cmake_minimum_required (VERSION 3.10)

#####################################################
## Variables to be set depending on project
#####################################################
set (PROJECTNAME "MyAwesomeGame") 

set (ENABLE_UNITTESTS OFF CACHE BOOL "enable unittests")
set (ENABLE_STRESSTEST OFF CACHE BOOL "enable stresstest")
set (ENABLE_WEB OFF CACHE BOOL "enable web build using SDL and em++")

#####################################################
## Other variables and compiler setup
#####################################################
set (CMAKE_CXX_STANDARD 17)
add_compile_definitions(DISABLE_CPP17_FILESYSTEM)
if(ENABLE_WEB)
	add_compile_definitions(MUSIC_OGG)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2 --std=c++17 -fpermissive ")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --use-preload-plugins --preload-file assets")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ASSERTIONS=1")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"bmp\",\"png\"]'")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL_TTF=2 -s USE_PTHREADS=1 -s USE_SDL_MIXER=2 -s USE_VORBIS=1 -s USE_OGG=1")
	add_definitions(-DENABLE_WEB)
else()
	if(WIN32)
		## nasty warning 5205 from tileson should not show up,
		## so the warning level of this one is set to 4 and the global warning level is set to three
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w45205 /W3 /EHsc -Ox")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 --std=c++17 -fpermissive -lstdc++fs")
	endif()
endif()

#####################################################
## Create Project file and link directories
#####################################################
project (${PROJECTNAME})
if(NOT ENABLE_WEB)
	if (WIN32)
		link_directories(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1/lib)
	endif()

	if (APPLE)
		link_directories(/usr/local/Cellar/sfml/2.4.2_1/lib/)
	endif()
endif()

#####################################################
## Setup Box2d
#####################################################
file(GLOB_RECURSE BOX2DFILES ext/box2d/Box2D/*)
add_library(Box2D ${BOX2DFILES})
target_include_directories(Box2D SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ext/box2d)

#####################################################
## setup JamTemplate
#####################################################

file(GLOB_RECURSE JAMTEMPLATEBASEFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/JamTemplate/common/*)
if(ENABLE_WEB)
	file(GLOB_RECURSE JAMTEMPLATEFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/JamTemplate/sdl/*)
else()
	file(GLOB_RECURSE JAMTEMPLATEFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/JamTemplate/sfml/*)
endif()

add_library(JamTemplate ${JAMTEMPLATEFILES} ${JAMTEMPLATEBASEFILES})

# add public includes, so they can be used by dependent targets
target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/JamTemplate/common)
target_include_directories(JamTemplate SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ext/tileson-master/include)
if(ENABLE_WEB)
	target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/JamTemplate/sdl)
else()
	target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/JamTemplate/sfml)
	target_include_directories(JamTemplate SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ext/SFML-2.5.1/include)
	target_include_directories(JamTemplate SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/usr/local/Cellar/sfml/2.4.2_1/include)
endif()

if(NOT ENABLE_WEB)
	# group together similar files for a cleaner JamTemplate Project in IDEs that support this feature
	source_group(GameLoop FILES src/JamTemplate/common/GameBase.cpp src/JamTemplate/common/GameBase.hpp src/JamTemplate/common/GameObject.hpp src/JamTemplate/common/GameState.cpp src/JamTemplate/common/GameState.hpp src/JamTemplate/sfml/Game.cpp src/JamTemplate/sfml/Game.hpp)
	source_group(SmartDrawables FILES src/JamTemplate/common/SmartAnimation.cpp src/JamTemplate/common/SmartAnimation.hpp src/JamTemplate/common/SmartBar.cpp src/JamTemplate/common/SmartBar.hpp src/JamTemplate/common/SmartDrawable.cpp src/JamTemplate/common/SmartDrawable.hpp src/JamTemplate/sfml/SmartShape.cpp src/JamTemplate/sfml/SmartShape.hpp src/JamTemplate/sfml/SmartSprite.cpp src/JamTemplate/sfml/SmartSprite.hpp src/JamTemplate/sfml/SmartText.cpp src/JamTemplate/sfml/SmartText.hpp src/JamTemplate/sfml/SmartTilemap.hpp src/JamTemplate/sfml/SmartTilemap.cpp)
	source_group(Tweens REGULAR_EXPRESSION src/JamTemplate/common/Tween*)

	target_link_libraries(JamTemplate optimized sfml-system )
	target_link_libraries(JamTemplate optimized sfml-window )
	target_link_libraries(JamTemplate optimized sfml-graphics )
	target_link_libraries(JamTemplate optimized sfml-audio )

	if (WIN32)
		target_link_libraries(JamTemplate debug sfml-system-d )
		target_link_libraries(JamTemplate debug sfml-window-d )
		target_link_libraries(JamTemplate debug sfml-graphics-d )
		target_link_libraries(JamTemplate debug sfml-audio-d )
	endif()
endif()

target_link_libraries(JamTemplate Box2D)

#####################################################
## setup StressTest
#####################################################
if (ENABLE_STRESSTEST)
	file(GLOB_RECURSE STRESSTESTFILES src/StressTest/*)
	
	add_executable(StressTest ${STRESSTESTFILES})
	if(ENABLE_WEB)
		set(CMAKE_EXECUTABLE_SUFFIX ".html")
	endif()
	target_link_libraries(StressTest JamTemplate)
	add_custom_command(TARGET StressTest PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/ ${CMAKE_CURRENT_BINARY_DIR}/assets)
endif()

#####################################################
## setup UnitTests
#####################################################
if (ENABLE_UNITTESTS)
	file(GLOB_RECURSE UNITTESTFILES src/UnitTests/*)
	
	# Download and unpack googletest at configure time
	configure_file(ext/googletest/CMakeLists.txt.in ${CMAKE_CURRENT_SOURCE_DIR}/ext/googletest/googletest-download/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ext/googletest/googletest-download )
	if(result)
	    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ext/googletest/googletest-download )
	if(result)
	    message(FATAL_ERROR "Build step for googletest failed: ${result}")
	endif()
	
	# Prevent overriding the parent project's compiler/linker
	# settings on Windows
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	
	# Add googletest directly to our build. This defines
	# the gtest and gtest_main targets.
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/googletest/googletest-src
					 ${CMAKE_CURRENT_SOURCE_DIR}/ext/googletest/googletest-build
					 EXCLUDE_FROM_ALL)
	
	# The gtest/gtest_main targets carry header search path
	# dependencies automatically when using CMake 2.8.11 or
	# later. Otherwise we have to add them here ourselves.
	if (CMAKE_VERSION VERSION_LESS 2.8.11)
		include_directories("${gtest_SOURCE_DIR}/include")
	endif()
	
	add_executable(UnitTests ${UNITTESTFILES})
	
	target_link_libraries(UnitTests gtest_main)
	target_link_libraries(UnitTests gmock)
	target_link_libraries(UnitTests JamTemplate)
	
	add_custom_command(TARGET UnitTests PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/ ${CMAKE_CURRENT_BINARY_DIR}/assets)
	add_test( UnitTests UnitTests )
endif()

#####################################################
## setup Game executable
#####################################################
file(GLOB GAMEFILES src/*)
add_executable(${PROJECTNAME}  ${GAMEFILES})
if(ENABLE_WEB)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

target_link_libraries(${PROJECTNAME} JamTemplate)

add_custom_command(TARGET ${PROJECTNAME} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)

#####################################################
## copy sfml dlls and .clang-format around
#####################################################
if (WIN32 AND NOT ENABLE_WEB)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1/bin/sfml-system-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1/bin/sfml-window-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1/bin/sfml-graphics-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
	configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1/bin/sfml-audio-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
	
	configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1/bin/sfml-system-d-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1/bin/sfml-window-d-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1/bin/sfml-graphics-d-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
	configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1/bin/sfml-audio-d-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
endif()
configure_file(${CMAKE_SOURCE_DIR}/.clang-format ${CMAKE_BINARY_DIR}/ COPYONLY)

#####################################################
## copy assets around
#####################################################
