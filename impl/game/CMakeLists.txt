file(GLOB GAMEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_executable(${PROJECTNAME} ${GAMEFILES})
if (JT_ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(${PROJECTNAME} PUBLIC "SHELL:--use-preload-plugins")
    target_link_options(${PROJECTNAME} PUBLIC --preload-file assets)
    target_link_options(${PROJECTNAME} PRIVATE "SHELL:-s TOTAL_MEMORY=256MB")
    target_link_options(${PROJECTNAME} PRIVATE "SHELL:-s ALLOW_MEMORY_GROWTH=1")
endif ()

target_link_libraries(${PROJECTNAME} GameLib)
target_include_directories(${PROJECTNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

jt_use_assets(${PROJECTNAME})
