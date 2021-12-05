message(STATUS "Fetching box2d")
FetchContent_Declare(
        box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.3.1
)

FetchContent_Populate(box2d)
FetchContent_GetProperties(box2d)

file(GLOB_RECURSE BOX2DFILES "${box2d_SOURCE_DIR}/Box2D/Box2D/*")
add_library(Box2D STATIC ${BOX2DFILES})
target_include_directories(Box2D SYSTEM PUBLIC ${box2d_SOURCE_DIR}/Box2D)
