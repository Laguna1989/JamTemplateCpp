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

function(jt_deploy_dlls_helper DESTFOLDER)
    if (WIN32)
        file(MAKE_DIRECTORY ${DESTFOLDER})
        # copy dlls

        if ($ENV{CLION_IDE})
            configure_file(${SFML_DIR_ROOT}/bin/sfml-system-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-window-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-graphics-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-audio-2.dll ${DESTFOLDER} COPYONLY)

            configure_file(${SFML_DIR_ROOT}/bin/sfml-system-d-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-window-d-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-graphics-d-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-audio-d-2.dll ${DESTFOLDER} COPYONLY)
        elseif (MSVC)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-system-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-window-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-graphics-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-audio-2.dll ${DESTFOLDER} COPYONLY)

            configure_file(${SFML_DIR_ROOT}/bin/sfml-system-d-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-window-d-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-graphics-d-2.dll ${DESTFOLDER} COPYONLY)
            configure_file(${SFML_DIR_ROOT}/bin/sfml-audio-d-2.dll ${DESTFOLDER} COPYONLY)

        endif ()
    endif ()
endfunction()


function(jt_deploy_dlls)
    if (NOT ENABLE_WEB)
        jt_deploy_dlls_helper(${CMAKE_CURRENT_BINARY_DIR})
    endif ()
endfunction()
