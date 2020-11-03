cmake_minimum_required (VERSION 3.16)

#####################################################
## Variables to be set depending on project
#####################################################
set (PROJECTNAME "MyAwesomeGame") 

set (ENABLE_UNITTESTS OFF CACHE BOOL "enable unittests")
set (ENABLE_STRESSTEST OFF CACHE BOOL "enable stresstest")

set (GAMEFILES 
	src/GameProperties.hpp
	src/GameProperties.cpp
	src/Hud.hpp
	src/Hud.cpp
	src/main.cpp
	src/main.hpp
	src/StateGame.hpp
	src/StateGame.cpp
	src/StateMenu.hpp
	src/StateMenu.cpp
	)

#####################################################
## Other variables and compiler setup
#####################################################
set (JAMTEMPLATEFILES 
	src/JamTemplate/Animation.cpp
	src/JamTemplate/Animation.hpp
	src/JamTemplate/Box2DObject.hpp
	src/JamTemplate/Button.hpp
	src/JamTemplate/Collision.hpp
	src/JamTemplate/Conversions.cpp
	src/JamTemplate/Conversions.hpp
	src/JamTemplate/Game.cpp
	src/JamTemplate/Game.hpp
	src/JamTemplate/GameObject.hpp
	src/JamTemplate/GameState.cpp
	src/JamTemplate/GameState.hpp
	src/JamTemplate/InputManager.cpp
	src/JamTemplate/InputManager.hpp
	src/JamTemplate/Lerp.hpp
	src/JamTemplate/MathHelper.cpp
	src/JamTemplate/MathHelper.hpp
	src/JamTemplate/Noise.hpp
	src/JamTemplate/ObjectGroup.hpp
	src/JamTemplate/PlayBar.hpp
	src/JamTemplate/PlayBar.cpp
	src/JamTemplate/Random.hpp
	src/JamTemplate/Random.cpp
	src/JamTemplate/SmartObject.cpp
	src/JamTemplate/SmartObject.hpp
	src/JamTemplate/SmartShape.hpp
	src/JamTemplate/SmartSprite.hpp
	src/JamTemplate/SmartText.hpp	
	src/JamTemplate/SplitString.hpp
	src/JamTemplate/SpriteFunctions.cpp
	src/JamTemplate/SpriteFunctions.hpp
	src/JamTemplate/TextureManager.cpp
	src/JamTemplate/TextureManager.hpp
	src/JamTemplate/Timer.hpp
	src/JamTemplate/Transform.hpp
	src/JamTemplate/TweenAlpha.hpp
	src/JamTemplate/TweenBase.hpp
	src/JamTemplate/TweenColor.hpp
	src/JamTemplate/TweenPosition.hpp
	src/JamTemplate/TweenRotation.hpp
	src/JamTemplate/TweenScale.hpp
	)

if(WIN32)
	set (CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /EHsc -Ox")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 --std=c++1z")
endif()


#####################################################
## Create Project file and link directories
#####################################################
project (${PROJECTNAME})

if (WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/lib)
endif()

if (APPLE)
    link_directories(/usr/local/Cellar/sfml/2.4.2_1/lib/)
endif()

#####################################################
## Setup Box2d
#####################################################
file(GLOB_RECURSE SRC_FILES ext/box2d/Box2D/*)
add_library(Box2D ${SRC_FILES})
target_include_directories(Box2D PRIVATE ext/box2d)

#####################################################
## setup JamTemplate
#####################################################
add_library(JamTemplate ${JAMTEMPLATEFILES})

# add public includes, so they can be used by dependent targets
target_include_directories(JamTemplate PUBLIC ext/SFML-2.5.1_win/include)
target_include_directories(JamTemplate PUBLIC ext/box2d)
target_include_directories(JamTemplate PUBLIC /usr/local/Cellar/sfml/2.4.2_1/include) 
target_include_directories(JamTemplate PUBLIC ext/tileson-master/include)

target_link_libraries(JamTemplate optimized sfml-system )
target_link_libraries(JamTemplate optimized sfml-window )
target_link_libraries(JamTemplate optimized sfml-graphics )

if (WIN32)
	target_link_libraries(JamTemplate debug sfml-system-d )
	target_link_libraries(JamTemplate debug sfml-window-d )
	target_link_libraries(JamTemplate debug sfml-graphics-d )
endif()

target_link_libraries(JamTemplate Box2D)

#####################################################
## setup StressTest
#####################################################
if (ENABLE_STRESSTEST)
	set (STRESSTESTFILES
		src/StressTest/main.cpp
		src/StressTest/MovementObject.hpp
		src/StressTest/Object.hpp
		src/StressTest/State1.cpp
		src/StressTest/State1.hpp
		src/StressTest/State2.cpp
		src/StressTest/State2.hpp
		src/StressTest/StateBox2d.cpp
		src/StressTest/StateBox2d.hpp
		src/StressTest/StateTileson.cpp
		src/StressTest/StateTileson.hpp
		src/StressTest/StateTween.cpp
		src/StressTest/StateTween.hpp
		src/StressTest/SwarmObject.hpp
	)

	add_executable(StressTest ${STRESSTESTFILES})
	target_link_libraries(StressTest JamTemplate)
endif()

#####################################################
## setup UnitTests
#####################################################
if (ENABLE_UNITTESTS)

	set (UNITTESTFILES
		src/UnitTests/ConversionsTest.cpp
		src/UnitTests/GameTest.cpp
		src/UnitTests/GameStateTest.cpp
		src/UnitTests/InputManagerTest.cpp
		src/UnitTests/MathHelperTest.cpp
		src/UnitTests/MockObject.hpp
		src/UnitTests/ObjectGroupTest.cpp
		src/UnitTests/RandomTest.cpp
		src/UnitTests/TextureManagerTest.cpp
		src/UnitTests/TimerTest.cpp
	)

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
	
endif()
#####################################################
## setup custom target to copy assets every time
#####################################################

# note: globbing is done only when cmake runs, so new files will be missing until cmake is run.
file(GLOB COPY_FILES
	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/assets/*)
	
add_custom_target(CopyAssets ALL
	# fake file that will never be present. This forces cmake to copy assets every time.
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/assets/__always_copy.txt	
	)
	
foreach(FILENAME ${COPY_FILES})
	set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}")
    set(DST "${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}")
	
	add_custom_command (
	TARGET CopyAssets
	COMMAND ${CMAKE_COMMAND} -E copy ${SRC} ${DST})
endforeach(FILENAME)

#####################################################
## setup Game executable
#####################################################
add_executable(${PROJECTNAME}  ${GAMEFILES})
target_link_libraries(${PROJECTNAME} JamTemplate)
add_dependencies(${PROJECTNAME} CopyAssets)

#####################################################
## copy sfml dlls and .clang-format around
#####################################################
if (WIN32)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-system-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-window-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-graphics-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
	
	configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-system-d-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-window-d-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-graphics-d-2.dll ${CMAKE_BINARY_DIR}/ COPYONLY)
endif()
configure_file(${CMAKE_SOURCE_DIR}/.clang-format ${CMAKE_BINARY_DIR}/ COPYONLY)

#####################################################
## copy assets around
#####################################################
#file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/ )
