cmake_minimum_required (VERSION 3.16)

#####################################################
## Variables to be set depending on project
#####################################################
set (PROJECTNAME "MyAwesomeGame") 

set (ENABLE_UNITTESTS OFF CACHE BOOL "enable unittests")
set (ENABLE_STRESSTEST OFF CACHE BOOL "enable stresstest")



#####################################################
## Other variables and compiler setup
#####################################################
file(GLOB GAMEFILES src/*)
file(GLOB_RECURSE JAMTEMPLATEFILES src/JamTemplate/*)

if(WIN32)
	set (CMAKE_CXX_STANDARD 17)
	## nasty warning 5205 from tileson should not show up,
	## so the warning level of this one is set to 4 and the global warning level is set to three
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w45205 /W3 /EHsc -Ox")
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
target_include_directories(JamTemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/JamTemplate)
target_include_directories(JamTemplate SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ext/SFML-2.5.1_win/include)
target_include_directories(JamTemplate SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ext/box2d)
target_include_directories(JamTemplate SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ext/tileson-master/include)
target_include_directories(JamTemplate SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/usr/local/Cellar/sfml/2.4.2_1/include) 

# group together similar files for a cleaner JamTemplate Project in IDEs that support this feature
source_group(GameLoop REGULAR_EXPRESSION src/JamTemplate/Game*)
source_group(SmartDrawables REGULAR_EXPRESSION src/JamTemplate/Smart*)
source_group(Tweens REGULAR_EXPRESSION src/JamTemplate/Tween*)

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
	file(GLOB_RECURSE STRESSTESTFILES src/StressTest/*)
	
	add_executable(StressTest ${STRESSTESTFILES})
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
	
endif()

#####################################################
## setup Game executable
#####################################################
add_executable(${PROJECTNAME}  ${GAMEFILES})
target_link_libraries(${PROJECTNAME} JamTemplate)
add_custom_command(TARGET ${PROJECTNAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)

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
