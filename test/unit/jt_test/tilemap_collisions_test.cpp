#include "tilemap/tilemap_collisions.hpp"
#include <gtest/gtest.h>

TEST(TilemapCollisions, emptyVector)
{
    jt::TilemapCollisions collisions {};
    collisions.refineColliders(16.0f);

    ASSERT_TRUE(collisions.getRects().empty());
}

TEST(TilemapCollisions, OneColliderStaysUntouched)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 16, 16 });
    collisions.refineColliders(16.0f);

    ASSERT_EQ(collisions.getRects().size(), 1);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);
}

TEST(TilemapCollisions, OneColliderStaysUntouchedDifferenzsize)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 32, 32 });
    collisions.refineColliders(32.0f);

    ASSERT_EQ(collisions.getRects().size(), 1);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);
}

TEST(TilemapCollisions, TwoSeparateCollidersHorizontalStayUntouched)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 1, 1 });
    collisions.add(jt::Rectf { 2, 0, 1, 1 });
    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), 2);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);

    ASSERT_FLOAT_EQ(collisions.getRects()[1].left, 2);
    ASSERT_FLOAT_EQ(collisions.getRects()[1].top, 0);
}

TEST(TilemapCollisions, TwoSeparateCollidersVerticalStayUntouched)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 1, 1 });
    collisions.add(jt::Rectf { 0, 2, 1, 1 });
    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), 2);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);

    ASSERT_FLOAT_EQ(collisions.getRects()[1].left, 0);
    ASSERT_FLOAT_EQ(collisions.getRects()[1].top, 2);
}

TEST(TilemapCollisions, TwoSeparateCollidersDiagonalStayUntouched)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 1, 1 });
    collisions.add(jt::Rectf { 1, 1, 1, 1 });
    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), 2);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);

    ASSERT_FLOAT_EQ(collisions.getRects()[1].left, 1);
    ASSERT_FLOAT_EQ(collisions.getRects()[1].top, 1);
}

TEST(TilemapCollisions, TwoSeparateCollidersDiagonal2StayUntouched)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 1, 1, 1 });
    collisions.add(jt::Rectf { 1, 0, 1, 1 });
    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), 2);
    ASSERT_FLOAT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_FLOAT_EQ(collisions.getRects()[0].top, 1);

    ASSERT_FLOAT_EQ(collisions.getRects()[1].left, 1);
    ASSERT_FLOAT_EQ(collisions.getRects()[1].top, 0);
}

TEST(TilemapCollisions, TwoCollidersHorizontalAreMerged)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 1, 1 });
    collisions.add(jt::Rectf { 1, 0, 1, 1 });
    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), 1);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);
    ASSERT_EQ(collisions.getRects()[0].width, 2);
    ASSERT_EQ(collisions.getRects()[0].height, 1);
}

TEST(TilemapCollisions, TwoCollidersVerticalAreMerged)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 1, 1 });
    collisions.add(jt::Rectf { 0, 1, 1, 1 });
    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), 1);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);
    ASSERT_EQ(collisions.getRects()[0].width, 1);
    ASSERT_EQ(collisions.getRects()[0].height, 2);
}

TEST(TilemapCollisions, ThreeCollidersHorizontalAreMerged)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 1, 1 });
    collisions.add(jt::Rectf { 1, 0, 1, 1 });
    collisions.add(jt::Rectf { 2, 0, 1, 1 });
    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), 1);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);
    ASSERT_EQ(collisions.getRects()[0].width, 3);
    ASSERT_EQ(collisions.getRects()[0].height, 1);
}

TEST(TilemapCollisions, TwoAndThreeCollidersHorizontalAreNotMerged)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 1, 1 });
    collisions.add(jt::Rectf { 1, 0, 1, 1 });
    collisions.add(jt::Rectf { 2, 0, 1, 1 });

    collisions.add(jt::Rectf { 1, 2, 1, 1 });
    collisions.add(jt::Rectf { 2, 2, 1, 1 });
    collisions.add(jt::Rectf { 3, 2, 1, 1 });

    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), 2);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);
    ASSERT_EQ(collisions.getRects()[0].width, 3);
    ASSERT_EQ(collisions.getRects()[0].height, 1);

    ASSERT_EQ(collisions.getRects()[1].left, 1);
    ASSERT_EQ(collisions.getRects()[1].top, 2);
    ASSERT_EQ(collisions.getRects()[1].width, 3);
    ASSERT_EQ(collisions.getRects()[1].height, 1);
}

TEST(TilemapCollisions, TwoXThreeCollidersHorizontalAreMerged)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 1, 1 });
    collisions.add(jt::Rectf { 1, 0, 1, 1 });
    collisions.add(jt::Rectf { 2, 0, 1, 1 });

    collisions.add(jt::Rectf { 0, 1, 1, 1 });
    collisions.add(jt::Rectf { 1, 1, 1, 1 });
    collisions.add(jt::Rectf { 2, 1, 1, 1 });

    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), 1);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);
    ASSERT_EQ(collisions.getRects()[0].width, 3);
    ASSERT_EQ(collisions.getRects()[0].height, 2);
}

TEST(TilemapCollisions, TCollidersAreMergedCorrectly)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 1, 1 });
    collisions.add(jt::Rectf { 1, 0, 1, 1 });
    collisions.add(jt::Rectf { 2, 0, 1, 1 });
    collisions.add(jt::Rectf { 1, 1, 1, 1 });

    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), 2);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);
    ASSERT_EQ(collisions.getRects()[0].width, 3);
    ASSERT_EQ(collisions.getRects()[0].height, 1);

    ASSERT_EQ(collisions.getRects()[1].left, 1);
    ASSERT_EQ(collisions.getRects()[1].top, 1);
    ASSERT_EQ(collisions.getRects()[1].width, 1);
    ASSERT_EQ(collisions.getRects()[1].height, 1);
}

TEST(TilemapCollisions, T90DegCollidersAreMergedCorrectly)
{
    jt::TilemapCollisions collisions {};
    collisions.add(jt::Rectf { 0, 0, 1, 1 });
    collisions.add(jt::Rectf { 0, 1, 1, 1 });
    collisions.add(jt::Rectf { 0, 2, 1, 1 });

    collisions.add(jt::Rectf { 1, 1, 1, 1 });

    collisions.refineColliders(1.0f);

    ASSERT_EQ(collisions.getRects().size(), 3);
    ASSERT_EQ(collisions.getRects()[0].left, 0);
    ASSERT_EQ(collisions.getRects()[0].top, 0);
    ASSERT_EQ(collisions.getRects()[0].width, 1);
    ASSERT_EQ(collisions.getRects()[0].height, 1);

    ASSERT_EQ(collisions.getRects()[1].left, 0);
    ASSERT_EQ(collisions.getRects()[1].top, 1);
    ASSERT_EQ(collisions.getRects()[1].width, 2);
    ASSERT_EQ(collisions.getRects()[1].height, 1);

    ASSERT_EQ(collisions.getRects()[2].left, 0);
    ASSERT_EQ(collisions.getRects()[2].top, 2);
    ASSERT_EQ(collisions.getRects()[2].width, 1);
    ASSERT_EQ(collisions.getRects()[2].height, 1);
}
