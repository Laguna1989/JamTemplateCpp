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

function(jt_deploy_dlls_helper_impl DESTFOLDER)
    configure_file(${SFML_DIR_ROOT}/bin/sfml-system-2.dll ${DESTFOLDER} COPYONLY)
    configure_file(${SFML_DIR_ROOT}/bin/sfml-window-2.dll ${DESTFOLDER} COPYONLY)
    configure_file(${SFML_DIR_ROOT}/bin/sfml-graphics-2.dll ${DESTFOLDER} COPYONLY)
    configure_file(${SFML_DIR_ROOT}/bin/sfml-audio-2.dll ${DESTFOLDER} COPYONLY)
    configure_file(${SFML_DIR_ROOT}/bin/openal32.dll ${DESTFOLDER} COPYONLY)

    configure_file(${SFML_DIR_ROOT}/bin/sfml-system-d-2.dll ${DESTFOLDER} COPYONLY)
    configure_file(${SFML_DIR_ROOT}/bin/sfml-window-d-2.dll ${DESTFOLDER} COPYONLY)
    configure_file(${SFML_DIR_ROOT}/bin/sfml-graphics-d-2.dll ${DESTFOLDER} COPYONLY)
    configure_file(${SFML_DIR_ROOT}/bin/sfml-audio-d-2.dll ${DESTFOLDER} COPYONLY)
endfunction()

function(jt_deploy_dlls_helper DESTFOLDER)
    if (WIN32)
        file(MAKE_DIRECTORY ${DESTFOLDER})
        # copy dlls

        if ($ENV{CLION_IDE})
            jt_deploy_dlls_helper_impl(${DESTFOLDER})
        elseif (MSVC)
            jt_deploy_dlls_helper_impl(${DESTFOLDER})
        endif ()
    endif ()
endfunction()


function(jt_deploy_dlls)
    if (NOT ENABLE_WEB)
        jt_deploy_dlls_helper(${CMAKE_CURRENT_BINARY_DIR})
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
