# tileson 1.4.0 uses std::find_if and friends in 17 headers without including <algorithm>.

foreach (header IN ITEMS tileson.h tileson_min.h)
    set(headerPath "${TILESON_INCLUDE_DIR}/${header}")
    if (NOT EXISTS ${headerPath})
        message(FATAL_ERROR "Cannot patch tileson: ${headerPath} does not exist")
    endif ()

    file(READ ${headerPath} headerContent)
    if (NOT headerContent MATCHES "#include <algorithm>")
        file(WRITE ${headerPath} "#include <algorithm>\n${headerContent}")
        message(STATUS "Patched ${header}: added missing <algorithm> include")
    endif ()
endforeach ()
