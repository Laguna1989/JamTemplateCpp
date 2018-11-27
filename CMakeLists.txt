cmake_minimum_required (VERSION 2.6)

set (PROJECTNAME "MyAwesomeGame") 

set (JAMTEMPLATEFILES 
	src/JamTemplate/GameObject.hpp
	src/JamTemplate/GameObject.cpp
	)


set (CMAKE_CXX_STANDARD 14)
project (${PROJECTNAME})

link_directories(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/lib)

add_library(JamTemplate ${JAMTEMPLATEFILES})
add_executable(${PROJECTNAME} src/main.cpp)

target_include_directories(JamTemplate PRIVATE ext/SFML-2.5.1_win/include)
target_link_libraries(JamTemplate sfml-system-d)
target_link_libraries(JamTemplate sfml-window-d)
target_link_libraries(JamTemplate sfml-graphics-d)


target_include_directories(${PROJECTNAME} PRIVATE ext/SFML-2.5.1_win/include)
target_link_libraries(${PROJECTNAME} sfml-system-d)
target_link_libraries(${PROJECTNAME} sfml-window-d)
target_link_libraries(${PROJECTNAME} sfml-graphics-d)
target_link_libraries(${PROJECTNAME} JamTemplate)

add_dependencies(${PROJECTNAME} JamTemplate)

## copy sfml dlls around
configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-system-d-2.dll ${BINARY_DIR}/ COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-window-d-2.dll ${BINARY_DIR}/ COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-graphics-d-2.dll ${BINARY_DIR}/ COPYONLY)