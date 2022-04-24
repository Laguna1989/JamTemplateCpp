#include <spatial_object_grid.hpp>
#include <gtest/gtest.h>

class TestObject { };

TEST(SpatialObjectGridTest, InitialGridIsEmpty)
{
    SpatialObjectGrid<TestObject> grid {};
    ASSERT_TRUE(grid.empty());
}

TEST(SpatialObjectGridTest, GridIsNotEmptyAfterPushBack)
{
    SpatialObjectGrid<TestObject> grid {};
    auto obj = std::make_shared<TestObject>();
    grid.push_back(obj);
    ASSERT_FALSE(grid.empty());
}
