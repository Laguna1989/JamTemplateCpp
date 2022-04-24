#include <spatial_object_grid.hpp>
#include <vector.hpp>
#include <gtest/gtest.h>

struct TestObject {
    jt::Vector2f getPosition() const { return m_position; }
    jt::Vector2f setPosition(jt::Vector2f const& newPosition) { m_position = newPosition; }

private:
    jt::Vector2f m_position {};
};

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

TEST(SpatialObjectGridTest, GetCorrectNumberOfNeighborsAroundCell)
{
    SpatialObjectGrid<TestObject> grid {};
    auto obj = std::make_shared<TestObject>();
    grid.push_back(obj);

    ASSERT_FALSE(true);
}
