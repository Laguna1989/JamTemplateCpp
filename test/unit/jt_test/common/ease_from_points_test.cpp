#include <ease/ease_from_points.hpp>
#include <gtest/gtest.h>

TEST(EaseFromPointsTest, TwoPointsStartEnd)
{
    jt::EaseFromPoints const ease { { { 0.0f, 0.0f }, { 1.0f, 1.0f } } };
    ASSERT_EQ(ease.easeIn(0.0f, 0.0f, 1.0f), 0.0f);

    ASSERT_EQ(ease.easeIn(1.0f, 0.0f, 1.0f), 1.0f);
}

TEST(EaseFromPointsTest, TwoPointsInBetween)
{
    jt::EaseFromPoints const ease { { { 0.0f, 0.0f }, { 1.0f, 1.0f } } };
    ASSERT_EQ(ease.easeIn(0.5f, 0.0f, 1.0f), 0.5f);
    ASSERT_EQ(ease.easeIn(0.25f, 0.0f, 1.0f), 0.25f);
    ASSERT_EQ(ease.easeIn(0.75f, 0.0f, 1.0f), 0.75f);
}

TEST(EaseFromPointsTest, ThreePointsInBetween)
{
    jt::EaseFromPoints const ease { { { 0.0f, 1.0f }, { 0.5f, 0.0f }, { 1.0f, 1.0f } } };
    ASSERT_EQ(ease.easeIn(0.5f, 0.0f, 1.0f), 0.0f);
    ASSERT_EQ(ease.easeIn(0.0f, 0.0f, 1.0f), 1.0f);
    ASSERT_EQ(ease.easeIn(1.0f, 0.0f, 1.0f), 1.0f);
    ASSERT_EQ(ease.easeIn(0.25f, 0.0f, 1.0f), 0.5f);
    ASSERT_EQ(ease.easeIn(0.75f, 0.0f, 1.0f), 0.5f);
}

TEST(EaseFromPointsTest, FourPointsValuesAndInBetween)
{
    jt::EaseFromPoints const ease { { { 0.0f, 1.0f }, { 0.5f, 0.5f }, { 1.0f, 0.6f } } };

    ASSERT_EQ(ease.easeIn(0.0f, 0.0f, 1.0f), 1.0f);
    ASSERT_EQ(ease.easeIn(0.25f, 0.0f, 1.0f), 0.75f);
    ASSERT_EQ(ease.easeIn(0.5f, 0.0f, 1.0f), 0.5f);
    ASSERT_EQ(ease.easeIn(0.75f, 0.0f, 1.0f), 0.55f);
    ASSERT_EQ(ease.easeIn(1.0f, 0.0f, 1.0f), 0.6f);
}
