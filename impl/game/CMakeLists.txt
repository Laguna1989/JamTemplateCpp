file(GLOB GAMEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_executable(${PROJECTNAME} ${GAMEFILES})
if (JT_ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

target_link_libraries(${PROJECTNAME} GameLib)
target_include_directories(${PROJECTNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

jt_use_assets(${PROJECTNAME})
