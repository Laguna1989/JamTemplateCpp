cmake_minimum_required (VERSION 2.6)

set (PROJECTNAME "MyAwesomeGame") 

set (JAMTEMPLATEFILES 
	src/JamTemplate/GameObject.hpp
	src/JamTemplate/GameObject.cpp
	src/JamTemplate/GameState.hpp
	src/JamTemplate/Timer.hpp
	src/JamTemplate/Transform.hpp
	src/JamTemplate/Game.hpp
	)

set (GAMEFILES 
	src/main.cpp
	src/StateMenu.hpp
	src/StateGame.hpp
	src/Player.hpp
	src/Player.cpp
	src/Balloon.hpp
	src/Shot.hpp
	)	

set (CMAKE_CXX_STANDARD 14)
project (${PROJECTNAME})

if (WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/lib)
endif (WIN32)

add_library(JamTemplate ${JAMTEMPLATEFILES})
add_executable(${PROJECTNAME}  ${GAMEFILES})

target_include_directories(JamTemplate PRIVATE ext/SFML-2.5.1_win/include)
target_link_libraries(JamTemplate sfml-system)
target_link_libraries(JamTemplate sfml-window)
target_link_libraries(JamTemplate sfml-graphics)


target_include_directories(${PROJECTNAME} PRIVATE ext/SFML-2.5.1_win/include)
target_link_libraries(${PROJECTNAME} sfml-system)
target_link_libraries(${PROJECTNAME} sfml-window)
target_link_libraries(${PROJECTNAME} sfml-graphics)
target_link_libraries(${PROJECTNAME} JamTemplate)

add_dependencies(${PROJECTNAME} JamTemplate)

## copy sfml dlls around
if (WIN32)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-system-2.dll ${BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-window-2.dll ${BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-graphics-2.dll ${BINARY_DIR}/ COPYONLY)
endif (WIN32)
