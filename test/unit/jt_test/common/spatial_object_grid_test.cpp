#include <game_object.hpp>
#include <spatial_object_grid.hpp>
#include <vector.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <type_traits>

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

class SpatialObjectGridParameterizedTestFixture : public ::testing::TestWithParam<jt::Vector2f> { };

TEST_P(SpatialObjectGridParameterizedTestFixture,
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

// clang-format off
INSTANTIATE_TEST_SUITE_P(SpatialObjectGridParametrizedTest,
    SpatialObjectGridParameterizedTestFixture,
    ::testing::Values(
        jt::Vector2f { 8.0f, 8.0f },
        jt::Vector2f { 0.0f, 0.0f },
        jt::Vector2f { 15.9f, 15.9f },
        jt::Vector2f { 8.0f, 0.0f },
        jt::Vector2f { 0.0f, 8.0f },
        jt::Vector2f { 15.9f, 0.0f },
        jt::Vector2f { 0.0f, 15.9f },
        jt::Vector2f { -15.9f, 0.0f },
        jt::Vector2f { 0.0f, -15.9f },
        jt::Vector2f { 31.9f, 0.0f },
        jt::Vector2f { 0.0f, 31.9f }
    ));
// clang-format on

TEST(SpatialObjectGridTest, GetObjectsAroundFromNeighboringCell)
{
    SpatialObjectGrid<TestObject, 16> grid {};
    auto obj = std::make_shared<TestObject>();
    obj->setPosition(jt::Vector2f { 17.0f, 0.0f });
    grid.push_back(obj);
    auto const objects = grid.getObjectsAround(jt::Vector2f { 8.0f, 8.0f }, 16.0f);
    ASSERT_FALSE(objects.empty());
    ASSERT_EQ(objects.size(), 1U);
    ASSERT_EQ(objects.at(0).lock(), obj);
}

TEST(SpatialObjectGridTest, GetObjectsAroundFromAllNeighboringCells)
{
    SpatialObjectGrid<TestObject, 16> grid {};

    // clang-format off
    std::vector<jt::Vector2f> positions {
        { 8.0f, 8.0f }, { 24.0f, 8.0f }, { 40.0f, 8.0f },
        { 8.0f, 24.0f }, { 24.0f, 24.0f }, { 40.0f, 24.0f },
        { 8.0f, 40.0f }, { 24.0f, 40.0f }, { 40.0f, 40.0f },
    };
    // clang-format on

    std::vector<std::shared_ptr<TestObject>> testObjects {};

    for (auto const& position : positions) {
        auto obj = std::make_shared<TestObject>();
        obj->setPosition(position);
        grid.push_back(obj);
        testObjects.push_back(obj);
    }

    auto const neighbors = grid.getObjectsAround(jt::Vector2f { 24.0f, 24.0f }, 16.0f);
    ASSERT_FALSE(testObjects.empty());
    ASSERT_EQ(testObjects.size(), 9U);
}

TEST(SpatialObjectGridTest, GetObjectsRoundsDistanceUp)
{
    SpatialObjectGrid<TestObject, 16> grid {};
    auto obj = std::make_shared<TestObject>();
    obj->setPosition(jt::Vector2f { 8.0f, 8.0f });
    grid.push_back(obj);
    auto const objects = grid.getObjectsAround(jt::Vector2f { 1.0f, 1.0f }, 1.0f);
    ASSERT_FALSE(objects.empty());
    ASSERT_EQ(objects.size(), 1U);
    ASSERT_EQ(objects.at(0).lock(), obj);
}

TEST(CellIndexTest, AddingTwoCellIndicesReturnsCorrectResult)
{
    jt::detail::CellIndex const index1 { 10, 20 };
    jt::detail::CellIndex const index2 { -5, 1 };
    jt::detail::CellIndex const expectedResult { 5, 21 };

    ASSERT_EQ(index1 + index2, expectedResult);
}

class SpatialObjectGridDistanceParameterizedTestFixture
    : public ::testing::TestWithParam<std::tuple<jt::Vector2f, float>> { };

TEST_P(SpatialObjectGridDistanceParameterizedTestFixture,
    GetObjectsAroundWithDistanceReturnsVectorWithCorrectEntryForOneObjectInCell)
{
    SpatialObjectGrid<TestObject, 16> grid {};
    auto obj = std::make_shared<TestObject>();
    obj->setPosition(jt::Vector2f { 8.0f, 8.0f });
    grid.push_back(obj);
    auto const objects = grid.getObjectsAround(std::get<0>(GetParam()), std::get<1>(GetParam()));
    ASSERT_FALSE(objects.empty());
    ASSERT_EQ(objects.size(), 1U);
    ASSERT_EQ(objects.at(0).lock(), obj);
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    SpatialObjectGridDistanceParameterizedTest,
    SpatialObjectGridDistanceParameterizedTestFixture,
    ::testing::Values(
        std::make_tuple(jt::Vector2f { 40.0f, 40.0f }, 24.0f),
        std::make_tuple(jt::Vector2f { 40.0f, 40.0f }, 16.1f),
        std::make_tuple(jt::Vector2f { 40.0f, 40.0f }, 32.0f),
        std::make_tuple(jt::Vector2f { 40.0f, 40.0f }, 96.0f),
        std::make_tuple(jt::Vector2f { 16.1f, 8.0f }, 24.0f),
        std::make_tuple(jt::Vector2f { 16.1f, 8.0f }, 16.1f),
        std::make_tuple(jt::Vector2f { 16.1f, 8.0f }, 32.0f),
        std::make_tuple(jt::Vector2f { 16.1f, 8.0f }, 96.0f),
        std::make_tuple(jt::Vector2f { 16.0f, 0.0f }, 16.1f),
        std::make_tuple(jt::Vector2f { -24.0f, 40.0f }, 24.0f)
));
// clang-format on

TEST(SpatialObjectGridTest, SpatialObjectGridIsInheritedFromGameObject)
{
    static_assert(std::is_base_of_v<jt::GameObject, jt::SpatialObjectGrid<TestObject, 16>>,
        "SpatialObjectGrid does not inherit from GameObject");
}

TEST(SpatialObjectGridTest, UpdateObjectCellIndex)
{
    SpatialObjectGrid<TestObject, 16> grid {};
    auto obj = std::make_shared<TestObject>();
    obj->setPosition(jt::Vector2f { 8.0f, 8.0f });
    grid.push_back(obj);
    obj->setPosition(jt::Vector2f { 24.0f, 8.0f });
    grid.update(0.1f);

    auto const objects = grid.getObjectsAround(jt::Vector2f { -8.0f, 8.0f }, 16.0f);
    ASSERT_TRUE(objects.empty());
}

// TODO next test: check that the object is actually in the right cell after update

TEST(SpatialObjectGridTest, CheckObjectBeingInCorrectCellAfterMove)
{
    SpatialObjectGrid<TestObject, 16> grid {};
    auto obj = std::make_shared<TestObject>();
    obj->setPosition(jt::Vector2f { 8.0f, 8.0f });
    grid.push_back(obj);
    obj->setPosition(jt::Vector2f { 24.0f, 8.0f });
    grid.update(0.1f);

    auto const objects = grid.getObjectsAround(jt::Vector2f { 24.0f, 8.0f }, 16.0f);
    ASSERT_FALSE(objects.empty());
}