cmake_minimum_required (VERSION 2.6)

#####################################################
## Variables to be set depending on project
#####################################################
set (PROJECTNAME "MyAwesomeGame") 

set (ENABLE_STRESSTEST OFF CACHE BOOL "enable stresstest")

set (GAMEFILES 
	src/GameProperties.hpp
	src/GameProperties.cpp
	src/Hud.hpp
	src/Hud.cpp
	src/main.cpp
	src/StateGame.hpp
	src/StateGame.cpp
	src/StateMenu.hpp
	src/StateMenu.cpp
	)

#####################################################
## Other variables and compiler setup
#####################################################
set (JAMTEMPLATEFILES 
	src/JamTemplate/Animation.hpp
	src/JamTemplate/Box2DObject.hpp
	src/JamTemplate/Button.hpp
	src/JamTemplate/Collision.hpp
	src/JamTemplate/Conversions.hpp
	src/JamTemplate/Game.hpp
	src/JamTemplate/GameObject.hpp
	src/JamTemplate/GameState.hpp
	src/JamTemplate/InputManager.hpp
	src/JamTemplate/InputManager.cpp
	src/JamTemplate/Lerp.hpp
	src/JamTemplate/MathHelper.hpp
	src/JamTemplate/Noise.hpp
	src/JamTemplate/ObjectGroup.hpp
	src/JamTemplate/PlayBar.hpp
	src/JamTemplate/PlayBar.cpp
	src/JamTemplate/Random.hpp
	src/JamTemplate/Random.cpp
	src/JamTemplate/SmartObject.hpp
	src/JamTemplate/SmartObject.cpp
	src/JamTemplate/SmartShape.hpp
	src/JamTemplate/SmartSprite.hpp
	src/JamTemplate/SmartText.hpp	
	src/JamTemplate/SplitString.hpp
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
	src/StressTest/StateTween.cpp
	src/StressTest/StateTween.hpp
	src/StressTest/SwarmObject.hpp
	)

if(WIN32)
	set (CMAKE_CXX_STANDARD 14)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 -Ox")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 --std=c++1z")
endif()


#####################################################
## Create projects and set them up accordingly
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
## setup other libs and executables
#####################################################
add_library(JamTemplate ${JAMTEMPLATEFILES})
add_executable(${PROJECTNAME}  ${GAMEFILES})


if (ENABLE_STRESSTEST)
	add_executable(StressTest ${STRESSTESTFILES})
	target_include_directories(StressTest PRIVATE ext/SFML-2.5.1_win/include)
	target_include_directories(StressTest PRIVATE ext/box2d)
	target_include_directories(StressTest PRIVATE /usr/local/Cellar/sfml/2.4.2_1/include) 
	target_link_libraries(StressTest optimized sfml-system )
	target_link_libraries(StressTest optimized sfml-window )
	target_link_libraries(StressTest optimized sfml-graphics )
	if (WIN32)
		target_link_libraries(StressTest debug sfml-system-d )
		target_link_libraries(StressTest debug sfml-window-d )
		target_link_libraries(StressTest debug sfml-graphics-d )
	endif()
	
	target_link_libraries(StressTest JamTemplate)
	target_link_libraries(StressTest Box2D)
endif()


target_include_directories(JamTemplate PRIVATE ext/SFML-2.5.1_win/include)
target_include_directories(JamTemplate PRIVATE ext/box2d)
target_include_directories(JamTemplate PRIVATE /usr/local/Cellar/sfml/2.4.2_1/include) 
target_link_libraries(JamTemplate optimized sfml-system )
target_link_libraries(JamTemplate optimized sfml-window )
target_link_libraries(JamTemplate optimized sfml-graphics )
target_link_libraries(JamTemplate Box2D)

if (WIN32)
	target_link_libraries(JamTemplate debug sfml-system-d )
	target_link_libraries(JamTemplate debug sfml-window-d )
	target_link_libraries(JamTemplate debug sfml-graphics-d )
endif()

target_include_directories(${PROJECTNAME} PRIVATE ext/SFML-2.5.1_win/include)
target_include_directories(${PROJECTNAME} PRIVATE ext/box2d/)
target_include_directories(${PROJECTNAME} PRIVATE /usr/local/Cellar/sfml/2.4.2_1/include) 
target_link_libraries(${PROJECTNAME} optimized sfml-window )
target_link_libraries(${PROJECTNAME} optimized sfml-system )
target_link_libraries(${PROJECTNAME} optimized sfml-graphics )
target_link_libraries(${PROJECTNAME} JamTemplate)
target_link_libraries(${PROJECTNAME} Box2D)


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
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/ )
