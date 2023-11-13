if (JT_ENABLE_DEMOS)
    add_subdirectory(demo)
endif ()
if (JT_ENABLE_PERFORMANCETESTS)
    if (NOT JT_ENABLE_WEB)
        ## google benchmark needs processor information,
        ## which is not available in web builds.
        add_subdirectory(performance)
    endif ()
endif ()
