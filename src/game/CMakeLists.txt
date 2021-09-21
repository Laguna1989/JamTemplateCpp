file(GLOB GAMEFILES ${CMAKE_CURRENT_SOURCE_DIR}/*)
file(GLOB HUDFILES ${CMAKE_CURRENT_SOURCE_DIR}/hud/*)

add_executable(${PROJECTNAME} ${GAMEFILES} ${HUDFILES})
if (ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

target_link_libraries(${PROJECTNAME} JamTemplate)
target_include_directories(${PROJECTNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

jt_use_assets(${PROJECTNAME})

jt_deploy_dlls()

