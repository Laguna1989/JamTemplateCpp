file(GLOB_RECURSE DEMOFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
FetchContent_GetProperties(imgui)
add_executable(jt_demos ${DEMOFILES} ${imgui_SOURCE_DIR}/imgui_demo.cpp)
if (JT_ENABLE_WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

target_include_directories(jt_demos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
FetchContent_GetProperties(api)
target_link_libraries(jt_demos JamTemplateLib ArbitraryPrecisionInteger)

if (NOT USE_SFML)
	if (WIN32)
		target_link_libraries(jt_demos SDL2::SDL2main)
		deploy_sdl_dlls()
	endif()
endif()

if (MSVC)
    target_compile_options(jt_demos PRIVATE "/W3")
    target_compile_options(jt_demos PRIVATE "/EHsc")
else ()
    target_compile_options(jt_demos PRIVATE "-Wall")
    target_compile_options(jt_demos PRIVATE "-Wextra")
endif ()

jt_use_assets(jt_demos)

