#include <tilemap/tilemap_collisions.hpp>
#include <gtest/gtest.h>

TEST(TilemapCollisions, emptyVector)
{
    jt::TilemapCollisions collisions {};
    collisions.refineColliders(16.0f);

    ASSERT_TRUE(collisions.getRects().empty());
}

class TilemapCollisionsRefineWithOneColliderTestFixture
    : public ::testing::TestWithParam<jt::Rectf> { };

TEST_P(TilemapCollisionsRefineWithOneColliderTestFixture, OneColliderStaysUntouched)
{
    jt::TilemapCollisions collisions {};
    jt::Rectf const expectedRefinedRect = GetParam();

    collisions.add(expectedRefinedRect);
    collisions.refineColliders(expectedRefinedRect.width);

    ASSERT_EQ(collisions.getRects().size(), 1);
    ASSERT_EQ(collisions.getRects()[0], expectedRefinedRect);
}

INSTANTIATE_TEST_SUITE_P(TilemapCollisionsRefineWithOneColliderTest,
    TilemapCollisionsRefineWithOneColliderTestFixture,
    ::testing::Values(jt::Rectf { 0.0f, 0.0f, 16.0f, 16.0f },
        jt::Rectf { 0.0f, 0.0f, 32.0f, 32.0f }, jt::Rectf { 0.0f, 0.0f, 64.0f, 64.0f },
        jt::Rectf { 0.0f, 0.0f, 1.0f, 1.0f }, jt::Rectf { 16.0f, 16.0f, 2.0f, 2.0f }));

class TilemapCollisionsRefineWithSeparateCollidersTestFixture
    : public ::testing::TestWithParam<std::vector<jt::Rectf>> { };

TEST_P(TilemapCollisionsRefineWithSeparateCollidersTestFixture, SeparateCollidersStayUntouched)
{
    jt::TilemapCollisions collisions {};
    for (auto const& c : GetParam()) {
        collisions.add(c);
    }

    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), GetParam().size());
    for (auto i = 0u; i != collisions.getRects().size(); ++i) {
        auto const& rectA = collisions.getRects().at(i);
        auto const& rectB = GetParam().at(i);

        ASSERT_EQ(rectA, rectB);
    }
}

INSTANTIATE_TEST_SUITE_P(TilemapCollisionsRefineWithSeparateCollidersTest,
    TilemapCollisionsRefineWithSeparateCollidersTestFixture,
    ::testing::Values(std::vector<jt::Rectf> { jt::Rectf { 0, 0, 1, 1 }, jt::Rectf { 2, 0, 1, 1 } },
        std::vector<jt::Rectf> { jt::Rectf { 0, 0, 1, 1 }, jt::Rectf { 0, 2, 1, 1 } },
        std::vector<jt::Rectf> { jt::Rectf { 0, 0, 1, 1 }, jt::Rectf { 1, 1, 1, 1 } },
        std::vector<jt::Rectf> { jt::Rectf { 0, 1, 1, 1 }, jt::Rectf { 1, 0, 1, 1 } }));

class TilemapCollisionsRefineWithMergeableCollidersTestFixture
    : public ::testing::TestWithParam<std::pair<std::vector<jt::Rectf>, std::vector<jt::Rectf>>> {
};

TEST_P(TilemapCollisionsRefineWithMergeableCollidersTestFixture, CollidersAreMerged)
{
    jt::TilemapCollisions collisions {};
    for (auto const& c : GetParam().first) {
        collisions.add(c);
    }

    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), GetParam().second.size());

    for (auto i = 0u; i != collisions.getRects().size(); ++i) {
        auto const& rectA = collisions.getRects().at(i);
        auto const& rectB = GetParam().second.at(i);

        ASSERT_EQ(rectA, rectB);
    }
}

INSTANTIATE_TEST_SUITE_P(TilemapCollisionsRefineWithMergeableCollidersTest,
    TilemapCollisionsRefineWithMergeableCollidersTestFixture,
    ::testing::Values(std::make_pair(std::vector<jt::Rectf> { jt::Rectf { 0, 0, 1, 1 },
                                         jt::Rectf { 1, 0, 1, 1 } },
                          std::vector<jt::Rectf> { jt::Rectf { 0, 0, 2, 1 } }),
        std::make_pair(
            std::vector<jt::Rectf> { jt::Rectf { 0, 0, 1, 1 }, jt::Rectf { 0, 1, 1, 1 } },
            std::vector<jt::Rectf> { jt::Rectf { 0, 0, 1, 2 } }),
        std::make_pair(std::vector<jt::Rectf> { jt::Rectf { 0, 0, 1, 1 }, jt::Rectf { 1, 0, 1, 1 },
                           jt::Rectf { 2, 0, 1, 1 } },
            std::vector<jt::Rectf> { jt::Rectf { 0, 0, 3, 1 } }),
        std::make_pair(std::vector<jt::Rectf> { jt::Rectf { 0, 0, 1, 1 }, jt::Rectf { 1, 0, 1, 1 },
                           jt::Rectf { 2, 0, 1, 1 }, jt::Rectf { 1, 2, 1, 1 },
                           jt::Rectf { 2, 2, 1, 1 }, jt::Rectf { 3, 2, 1, 1 } },
            std::vector<jt::Rectf> { jt::Rectf { 0, 0, 3, 1 }, jt::Rectf { 1, 2, 3, 1 } }),
        std::make_pair(std::vector<jt::Rectf> { jt::Rectf { 0, 0, 1, 1 }, jt::Rectf { 1, 0, 1, 1 },
                           jt::Rectf { 2, 0, 1, 1 }, jt::Rectf { 0, 1, 1, 1 },
                           jt::Rectf { 1, 1, 1, 1 }, jt::Rectf { 2, 1, 1, 1 } },
            std::vector<jt::Rectf> { jt::Rectf { 0, 0, 3, 2 } }),
        std::make_pair(std::vector<jt::Rectf> { jt::Rectf { 0, 0, 1, 1 }, jt::Rectf { 1, 0, 1, 1 },
                           jt::Rectf { 2, 0, 1, 1 }, jt::Rectf { 1, 1, 1, 1 } },
            std::vector<jt::Rectf> { jt::Rectf { 0, 0, 3, 1 }, jt::Rectf { 1, 1, 1, 1 } }),
        std::make_pair(std::vector<jt::Rectf> { jt::Rectf { 0, 0, 1, 1 }, jt::Rectf { 0, 1, 1, 1 },
                           jt::Rectf { 0, 2, 1, 1 }, jt::Rectf { 1, 1, 1, 1 } },
            std::vector<jt::Rectf> {
                jt::Rectf { 0, 0, 1, 1 }, jt::Rectf { 0, 1, 2, 1 }, jt::Rectf { 0, 2, 1, 1 } })));
