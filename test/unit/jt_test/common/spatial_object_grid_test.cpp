#include <spatial_object_grid.hpp>
#include <vector.hpp>
#include <gtest/gtest.h>

struct TestObject {
    jt::Vector2f getPosition() const { return m_position; }
    void setPosition(jt::Vector2f const& newPosition) { m_position = newPosition; }

private:
    jt::Vector2f m_position {};
};

using jt::SpatialObjectGrid;

TEST(SpatialObjectGridTest, InitialGridIsEmpty)
{
    SpatialObjectGrid<TestObject, 16> grid {};
    ASSERT_TRUE(grid.empty());
}

TEST(SpatialObjectGridTest, GridIsNotEmptyAfterPushBack)
{
    SpatialObjectGrid<TestObject, 16> grid {};
    auto obj = std::make_shared<TestObject>();
    grid.push_back(obj);
    ASSERT_FALSE(grid.empty());
}

TEST(SpatialObjectGridTest, GetObjectsAroundReturnsEmptyVectorIfGridEmpty)
{
    SpatialObjectGrid<TestObject, 16> grid {};
    ASSERT_TRUE(grid.getObjectsAround(jt::Vector2f { 0.0f, 0.0f }, 16.0f).empty());
}

TEST(SpatialObjectGridTest, GetObjectsAroundReturnsEmptyVectorIfCellEmpty)
{
    SpatialObjectGrid<TestObject, 16> grid {};
    auto obj = std::make_shared<TestObject>();
    obj->setPosition(jt::Vector2f { 5000.0f, 5000.0f });
    grid.push_back(obj);
    ASSERT_TRUE(grid.getObjectsAround(jt::Vector2f { 0.0f, 0.0f }, 16.0f).empty());
}

class SpatialObjectGridParametrizedTestFixture : public ::testing::TestWithParam<jt::Vector2f> { };

TEST_P(SpatialObjectGridParametrizedTestFixture,
    GetObjectsAroundReturnsVectorWithCorrectEntryForOneObjectInCell)
{
    SpatialObjectGrid<TestObject, 16> grid {};
    auto obj = std::make_shared<TestObject>();
    obj->setPosition(GetParam());
    grid.push_back(obj);
    auto const objects = grid.getObjectsAround(jt::Vector2f { 8.0f, 8.0f }, 16.0f);
    ASSERT_FALSE(objects.empty());
    ASSERT_EQ(obj, objects.at(0).lock());
}

INSTANTIATE_TEST_SUITE_P(SpatialObjectGridParametrizedTest,
    SpatialObjectGridParametrizedTestFixture, ::testing::Values(jt::Vector2f { 8.0f, 8.0f }));

TEST(SpatialObjectGridTest, GetObjectsAroundReturnsVectorWithCorrectEntryForOneObjectInCell)
{
    SpatialObjectGrid<TestObject, 16> grid {};
    auto obj = std::make_shared<TestObject>();
    obj->setPosition(jt::Vector2f { 8.0f, 8.0f });
    grid.push_back(obj);
    auto const objects = grid.getObjectsAround(jt::Vector2f { 8.0f, 8.0f }, 16.0f);
    ASSERT_FALSE(objects.empty());
    ASSERT_EQ(obj, objects.at(0).lock());
}
