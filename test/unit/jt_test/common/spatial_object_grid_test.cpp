#include <spatial_object_grid.hpp>
#include <gtest/gtest.h>

class TestObject { };

TEST(SpatialObjectGridTest, InitialGridIsEmpty)
{
    SpatialObjectGrid<TestObject> grid {};

    ASSERT_TRUE(grid.empty());
}
