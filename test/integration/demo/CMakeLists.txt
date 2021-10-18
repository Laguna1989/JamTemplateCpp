file(GLOB_RECURSE DEMOFILES ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(jt_demos ${DEMOFILES})
if (ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()
target_link_libraries(jt_demos JamTemplate)
jt_use_assets(jt_demos)
jt_deploy_dlls()

