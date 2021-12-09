#include "rect.hpp"
#include <gtest/gtest.h>

TEST(RectEQ, Equal)
{
    jt::Rectf const initial { 5.0f, -1.245f, 44.1f, 2.2f };
    jt::Rectf const initial2 { initial };

    EXPECT_TRUE(initial == initial2);
    EXPECT_FALSE(initial != initial2);
}

TEST(RectEQ, NotEqual)
{
    jt::Rectf const initial { 5.0f, -1.245f, 44.1f, 2.2f };
    jt::Rectf const initial2 { 0.0f, 0.0f, 0.0f, 0.0f };

    EXPECT_FALSE(initial == initial2);
    EXPECT_TRUE(initial != initial2);
}

TEST(RectIEQ, Equal)
{
    jt::Recti const initial { 5, -1, 44, 2 };
    jt::Recti const initial2 { initial };

    EXPECT_TRUE(initial == initial2);
    EXPECT_FALSE(initial != initial2);
}

TEST(RectIEQ, NotEqual)
{
    jt::Recti const initial { 5, -1, 44, 2 };
    jt::Recti const initial2 { 0, 0, 0, 0 };

    EXPECT_FALSE(initial == initial2);
    EXPECT_TRUE(initial != initial2);
}

TEST(Rect, ReadAccess)
{
    float const left { 5.1f };
    float const top { -1.1111f };
    float const width { 22.44f };
    float const height { 2.88f };
    jt::Rectf const r { left, top, width, height };

    EXPECT_EQ(r.left, left);
    EXPECT_EQ(r.top, top);
    EXPECT_EQ(r.width, width);
    EXPECT_EQ(r.height, height);
}

TEST(RectAccess, WriteAccess)
{
    float const left { 5.1f };
    float const top { -1.1111f };
    float const width { 22.44f };
    float const height { 2.88f };
    jt::Rectf r {};

    r.left = left;
    r.top = top;
    r.width = width;
    r.height = height;

    EXPECT_EQ(r.left, left);
    EXPECT_EQ(r.top, top);
    EXPECT_EQ(r.width, width);
    EXPECT_EQ(r.height, height);
}

TEST(RectiAccess, ReadAccess)
{
    int const left { 5 };
    int const top { -1 };
    int const width { 22 };
    int const height { 2 };
    jt::Recti const r { left, top, width, height };

    EXPECT_EQ(r.left, left);
    EXPECT_EQ(r.top, top);
    EXPECT_EQ(r.width, width);
    EXPECT_EQ(r.height, height);
}

TEST(RectiAccess, WriteAccess)
{
    int const left { 5 };
    int const top { -1 };
    int const width { 22 };
    int const height { 2 };
    jt::Recti r {};

    r.left = left;
    r.top = top;
    r.width = width;
    r.height = height;

    EXPECT_EQ(r.left, left);
    EXPECT_EQ(r.top, top);
    EXPECT_EQ(r.width, width);
    EXPECT_EQ(r.height, height);
}
