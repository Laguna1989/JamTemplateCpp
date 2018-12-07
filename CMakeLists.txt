cmake_minimum_required (VERSION 2.6)

#####################################################
## Variables to be set depending on project
#####################################################
set (PROJECTNAME "MyAwesomeGame") 

set (GAMEFILES 
	src/main.cpp
	src/Player.cpp
	)	

#####################################################
## Other variables and compiler setup
#####################################################
set (JAMTEMPLATEFILES 
	src/JamTemplate/Random.cpp
	src/JamTemplate/TextureManager.cpp
	)


set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3")


#####################################################
## Create projects and set them up accordingly
#####################################################
project (${PROJECTNAME})

if (WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/lib)
endif (WIN32)

if (APPLE)
    link_directories(/usr/local/Cellar/sfml/2.4.2_1/lib/)
endif (APPLE)

add_library(JamTemplate ${JAMTEMPLATEFILES})
add_executable(${PROJECTNAME}  ${GAMEFILES})

target_include_directories(JamTemplate PRIVATE ext/SFML-2.5.1_win/include)
target_include_directories(JamTemplate PRIVATE /usr/local/Cellar/sfml/2.4.2_1/include) 
target_link_libraries(JamTemplate optimized sfml-system )
target_link_libraries(JamTemplate optimized sfml-window )
target_link_libraries(JamTemplate optimized sfml-graphics )

if (WIN32)
	target_link_libraries(JamTemplate debug sfml-system-d )
	target_link_libraries(JamTemplate debug sfml-window-d )
	target_link_libraries(JamTemplate debug sfml-graphics-d )
endif (WIN32)

target_include_directories(${PROJECTNAME} PRIVATE ext/SFML-2.5.1_win/include)
target_include_directories(${PROJECTNAME} PRIVATE /usr/local/Cellar/sfml/2.4.2_1/include) 
target_link_libraries(${PROJECTNAME} optimized sfml-system )
target_link_libraries(${PROJECTNAME} optimized sfml-window )
target_link_libraries(${PROJECTNAME} optimized sfml-graphics )
target_link_libraries(${PROJECTNAME} JamTemplate)

target_link_libraries(${PROJECTNAME} JamTemplate)

#####################################################
## copy sfml dlls around
#####################################################
if (WIN32)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-system-2.dll ${BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-window-2.dll ${BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-graphics-2.dll ${BINARY_DIR}/ COPYONLY)
	
	configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-system-d-2.dll ${BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-window-d-2.dll ${BINARY_DIR}/ COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/ext/SFML-2.5.1_win/bin/sfml-graphics-d-2.dll ${BINARY_DIR}/ COPYONLY)
endif (WIN32)
