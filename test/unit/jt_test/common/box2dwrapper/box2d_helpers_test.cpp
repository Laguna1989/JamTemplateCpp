#include <box2dwrapper/box2d_helpers.hpp>
#include <box2dwrapper/box2d_world_impl.hpp>
#include <gtest/gtest.h>
#include <cstdint>

namespace {
enum TestCategory : std::uint64_t {
    eCategoryA = 0x2,
    eCategoryB = 0x4,
    eCategoryC = 0x8,
};

struct CategoryPairParams {
    std::uint64_t shape1Category;
    std::uint64_t shape2Category;
    std::uint64_t a;
    std::uint64_t b;
    bool expected;
};
} // namespace

class Box2dHelpersIsCategoryPairTest : public ::testing::TestWithParam<CategoryPairParams> {
public:
    jt::Box2DWorldImpl m_world { jt::Vector2f {} };

    b2ShapeId createShape(std::uint64_t const category)
    {
        auto const body = m_world.createBody(b2DefaultBodyDef());
        auto shapeDef = b2DefaultShapeDef();
        shapeDef.filter.categoryBits = category;
        auto const box = b2MakeBox(1.0f, 1.0f);
        return b2CreatePolygonShape(body, &shapeDef, &box);
    }
};

TEST_P(Box2dHelpersIsCategoryPairTest, ReturnsExpectedValue)
{
    auto const& p = GetParam();
    auto const shape1 = createShape(p.shape1Category);
    auto const shape2 = createShape(p.shape2Category);
    ASSERT_EQ(jt::Box2DHelpers::isCategoryPair(shape1, shape2, p.a, p.b), p.expected);
}

INSTANTIATE_TEST_SUITE_P(Box2dHelpersIsCategoryPairTest, Box2dHelpersIsCategoryPairTest,
    ::testing::Values(
        // matching order
        CategoryPairParams { eCategoryA, eCategoryB, eCategoryA, eCategoryB, true },
        // swapped order
        CategoryPairParams { eCategoryB, eCategoryA, eCategoryA, eCategoryB, true },
        // only one shape matches
        CategoryPairParams { eCategoryA, eCategoryC, eCategoryA, eCategoryB, false },
        // both shapes in the same of the two categories
        CategoryPairParams { eCategoryA, eCategoryA, eCategoryA, eCategoryB, false },
        // same category requested twice
        CategoryPairParams { eCategoryA, eCategoryA, eCategoryA, eCategoryA, true },
        // neither shape matches
        CategoryPairParams { eCategoryC, eCategoryC, eCategoryA, eCategoryB, false },
        // multi bit argument matches any of its bits
        CategoryPairParams { eCategoryC, eCategoryB, eCategoryA | eCategoryC, eCategoryB, true },
        // shape with multiple category bits
        CategoryPairParams {
            eCategoryA | eCategoryB, eCategoryC, eCategoryB, eCategoryC, true }));
