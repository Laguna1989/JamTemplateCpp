file(GLOB_RECURSE DEMOFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
FetchContent_GetProperties(imgui)
add_executable(jt_demos ${DEMOFILES} ${imgui_SOURCE_DIR}/imgui_demo.cpp)

if (JT_ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(jt_demos PUBLIC "SHELL:--use-preload-plugins")
    target_link_options(jt_demos PUBLIC --preload-file assets)
    target_link_options(jt_demos PRIVATE "SHELL:-s TOTAL_MEMORY=256MB")
    target_link_options(jt_demos PRIVATE "SHELL:-s ALLOW_MEMORY_GROWTH=1")
endif ()


target_include_directories(jt_demos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(jt_demos JamTemplateLib)
jt_use_assets(jt_demos)

