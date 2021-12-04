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
