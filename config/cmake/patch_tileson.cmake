# tileson 1.4.0 relies on transitive standard library includes that newer compilers no longer provide:
# - tileson.h / tileson_min.h use std::find_if and friends without including <algorithm>.
# - json11.hpp, Color.hpp and Tools.hpp use uint8_t without including <cstdint> (fails with GCC 16).
# Prepending to tileson.h also covers json11.hpp, Color.hpp and Tools.hpp, which are only included from there.
# json11.hpp is patched directly as well, as tileson_min.h users provide/include it themselves.

function(prependMissingIncludes header)
    set(headerPath "${TILESON_INCLUDE_DIR}/${header}")
    if (NOT EXISTS ${headerPath})
        message(FATAL_ERROR "Cannot patch tileson: ${headerPath} does not exist")
    endif ()

    file(READ ${headerPath} headerContent)
    set(changed FALSE)
    foreach (include IN LISTS ARGN)
        string(FIND "${headerContent}" "#include <${include}>" includePosition)
        if (includePosition EQUAL -1)
            set(headerContent "#include <${include}>\n${headerContent}")
            set(changed TRUE)
            message(STATUS "Patched ${header}: added missing <${include}> include")
        endif ()
    endforeach ()

    if (changed)
        file(WRITE ${headerPath} "${headerContent}")
    endif ()
endfunction()

prependMissingIncludes(tileson.h algorithm cstdint)
prependMissingIncludes(tileson_min.h algorithm cstdint)
prependMissingIncludes(external/json11.hpp cstdint)
