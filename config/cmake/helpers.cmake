function(jt_use_assets TGT)
    add_custom_command(TARGET ${TGT} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)

    if (MSVC)
        add_custom_command(TARGET ${TGT} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/Debug/assets)
        add_custom_command(TARGET ${TGT} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/Release/assets)
    endif ()
endfunction()

function(target_link_libraries_system target)
    set(libs ${ARGN})
    foreach (lib ${libs})
        get_target_property(lib_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)
        target_include_directories(${target} SYSTEM PRIVATE ${lib_include_dirs})
        target_link_libraries(${target} ${lib})
    endforeach (lib)
endfunction(target_link_libraries_system)

function(deploy_sdl_dlls)
    if(WIN32)
        FETCHCONTENT_GETPROPERTIES(sdl2)
        FETCHCONTENT_GETPROPERTIES(sdl2-image)
        FETCHCONTENT_GETPROPERTIES(sdl2-ttf)
        configure_file(${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
        configure_file(${sdl2-image_SOURCE_DIR}/lib/x64/SDL2_image.dll ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
        configure_file(${sdl2-ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.dll ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
    else ()
        message(STATUS "No dlls to copy on non-windows system")
    endif()
endfunction()


function (mac_sdl_setup)
    if (NOT USE_SFML)
        if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            include_directories(/usr/local/Cellar/sdl2/2.0.22/include/
                    /usr/local/Cellar/sdl2_image/2.0.5/include/
                    /usr/local/Cellar/sdl2_ttf/2.0.18_1/include/)
        endif()
    endif()
endfunction()

function (setup_sfml)
    FetchContent_GetProperties(sfml)
    # Apple users: set to /usr/local/Cellar/sfml/2.4.2_1/lib/ or respectively
    if (WIN32)
        set(SFML_DIR_ROOT "${sfml_SOURCE_DIR}" CACHE PATH "Path to SFML root dir.")
    endif ()

    if ($ENV{CLION_IDE})
        set(SFML_DIR "${SFML_DIR_ROOT}/lib/cmake/SFML")
    endif ()
    if (WIN32 OR APPLE)
        link_directories(${SFML_DIR_ROOT}/lib)
    endif ()
endfunction()

function (setup_sdl)
    if (WIN32)
        FETCHCONTENT_GETPROPERTIES(sdl2)
        FETCHCONTENT_GETPROPERTIES(sdl2-image)
        FETCHCONTENT_GETPROPERTIES(sdl2-ttf)
        message(STATUS "sdl2_SOURCE_DIR: ${sdl2_SOURCE_DIR}")
        message(STATUS "sdl2-image_SOURCE_DIR: ${sdl2-image_SOURCE_DIR}")
        message(STATUS "sdl2-ttf_SOURCE_DIR: ${sdl2-ttf_SOURCE_DIR}")

        set(SDL2_DIR "${sdl2_SOURCE_DIR}/cmake" CACHE PATH "Path to sdl2 root dir.")
        find_package(SDL2 REQUIRED)

        set(sdl2_image_DIR "${sdl2-image_SOURCE_DIR}/cmake" CACHE PATH "Path to sdl2_image root dir.")
        find_package(sdl2_image REQUIRED)

        set(sdl2_ttf_DIR "${sdl2-ttf_SOURCE_DIR}/cmake" CACHE PATH "Path to sdl2_ttf root dir.")
        find_package(sdl2_ttf REQUIRED)
    else()
        message(STATUS "non-windows systems it is expected that sdl2, sdl2_image and sdl2_ttf is already installed")
        if(NOT JT_ENABLE_WEB)
            find_package(SDL2 REQUIRED)
            include(FindPkgConfig)
            pkg_check_modules(SDL2_Image REQUIRED IMPORTED_TARGET SDL2_image)
            pkg_check_modules(SDL2_TTF REQUIRED IMPORTED_TARGET SDL2_ttf)
        endif()
    endif()
    # on non-windows it is expected that sdl is available on the system
endfunction()

function(jt_setup_fmod)
    if(MSVC)
        ## Windows
        set(FMOD_DIR "${CMAKE_SOURCE_DIR}/ext/fmod/win" CACHE INTERNAL "fmod directory")
    elseif (APPLE)
        ## Mac
        set(FMOD_DIR "${CMAKE_SOURCE_DIR}/ext/fmod/mac" CACHE INTERNAL "fmod directory")

    elseif (EMSCRIPTEN)
        ## Web

        add_link_options("SHELL:-s EXPORTED_RUNTIME_METHODS=['cwrap','setValue','getValue']")

        set(FMOD_DIR "${CMAKE_SOURCE_DIR}/ext/fmod/html5" CACHE INTERNAL "fmod directory")
    else()
        ## Linux
        set(FMOD_DIR "${CMAKE_SOURCE_DIR}/ext/fmod/linux" CACHE INTERNAL "fmod directory")
    endif()
endfunction()

function(jt_link_fmod TGT)
    message(STATUS "FMOD_DIR: ${FMOD_DIR}")
    if(MSVC)

        target_include_directories(${TGT} PUBLIC ${FMOD_DIR}/api/core/inc)
        target_include_directories(${TGT} PUBLIC ${FMOD_DIR}/api/studio/inc)

        target_link_directories(${TGT} PUBLIC ${FMOD_DIR}/api/core/lib/x64)
        target_link_directories(${TGT} PUBLIC ${FMOD_DIR}/api/studio/lib/x64)

        target_link_libraries(${TGT} PUBLIC fmod_vc)
        target_link_libraries(${TGT} PUBLIC fmodstudio_vc)
        
        add_custom_command(TARGET ${TGT} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${FMOD_DIR}/lib/fmod.dll ${CMAKE_CURRENT_BINARY_DIR}/)

        add_custom_command(TARGET ${TGT} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${FMOD_DIR}/lib/fmodstudio.dll ${CMAKE_CURRENT_BINARY_DIR}/)

    elseif (APPLE)

        target_include_directories(${TGT} PUBLIC ${FMOD_DIR}/api/core/inc)
        target_include_directories(${TGT} PUBLIC ${FMOD_DIR}/api/studio/inc)

        target_link_directories(${TGT} PUBLIC ${FMOD_DIR}/api/core/lib)
        target_link_directories(${TGT} PUBLIC ${FMOD_DIR}/api/studio/lib)

        target_link_libraries(${TGT} PUBLIC ${FMOD_DIR}/api/core/lib/libfmod.dylib)
        target_link_libraries(${TGT} PUBLIC ${FMOD_DIR}/api/studio/lib/libfmodstudio.dylib)

        add_custom_command(TARGET ${TGT} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${FMOD_DIR}/api/core/lib/libfmod.dylib ${CMAKE_CURRENT_BINARY_DIR}/)

        add_custom_command(TARGET ${TGT} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${FMOD_DIR}/api/studio/lib/libfmodstudio.dylib ${CMAKE_CURRENT_BINARY_DIR}/)

    elseif (EMSCRIPTEN)
        add_link_options("SHELL:-s EXPORTED_RUNTIME_METHODS=['cwrap','setValue','getValue']")

        target_include_directories(${TGT} PUBLIC ${FMOD_DIR}/api/core/inc)
        target_include_directories(${TGT} PUBLIC ${FMOD_DIR}/api/studio/inc)

        target_link_libraries(${TGT} PUBLIC ${FMOD_DIR}/api/core/lib/upstream/w32/fmod_wasm.a)
        target_link_libraries(${TGT} PUBLIC ${FMOD_DIR}/api/studio/lib/upstream/w32/fmodstudio_wasm.a)
    else()
        ## Linux

        add_custom_command(TARGET ${TGT} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${FMOD_DIR}/api/core/lib/x86_64/libfmod.* ${CMAKE_CURRENT_BINARY_DIR}/)

        target_include_directories(${TGT} PUBLIC ${FMOD_DIR}/api/core/inc)
        target_include_directories(${TGT} PUBLIC ${FMOD_DIR}/api/studio/inc)

        target_link_directories(${TGT} PUBLIC ${FMOD_DIR}/api/core/lib/x86_64)
        target_link_directories(${TGT} PUBLIC ${FMOD_DIR}/api/studio/lib/x86_64)

        target_link_libraries(${TGT} PUBLIC ${FMOD_DIR}/api/core/lib/x86_64/libfmod.so)
        target_link_libraries(${TGT} PUBLIC ${FMOD_DIR}/api/studio/lib/x86_64/libfmodstudio.so)

    endif()

endfunction()
