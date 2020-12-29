#include "Vector.hpp"
#include "gtest/gtest.h"

TEST(VectorEQ, Equal)
{
    jt::Vector2 const initial { 5.0f, -1.245f };
    jt::Vector2 const initial2 { initial };

    EXPECT_TRUE(initial == initial2);
    EXPECT_FALSE(initial != initial2);
}

TEST(VectorEQ, NotEqual)
{
    jt::Vector2 const initial { 5.0f, -1.245f };
    jt::Vector2 const add { 0.0f, 0.0f };

    EXPECT_FALSE(initial == add);
    EXPECT_TRUE(initial != add);
}

TEST(VectorAdd, AddZereo)
{
    jt::Vector2 const initial { 5.0f, -1.245f };
    jt::Vector2 const add { 0.0f, 0.0f };

    EXPECT_EQ(initial, initial + add);
}

TEST(VectorAdd, AddReal)
{
    jt::Vector2 const initial { 5.0f, -1.245f };
    jt::Vector2 const add { 1.0f, 1.0f };
    jt::Vector2 const expected { initial.x() + add.x(), initial.y() + add.y() };

    EXPECT_EQ(initial + add, expected);
}

TEST(VectorAddEQ, AddZero)
{
    jt::Vector2 const initial { 5.0f, -1.245f };
    jt::Vector2 copy { initial };
    jt::Vector2 const add { 0.0f, 0.0f };
    copy += add;
    EXPECT_EQ(copy, initial);
}

TEST(VectorAddEQ, AddReal)
{
    jt::Vector2 initial { 5.0f, -1.245f };
    jt::Vector2 const add { 1.0f, -1.0f };
    jt::Vector2 const expected { initial.x() + add.x(), initial.y() + add.y() };
    initial += add;
    EXPECT_EQ(initial, expected);
}

TEST(VectorAdd, SubtractZereo)
{
    jt::Vector2 const initial { 5.0f, -1.245f };
    jt::Vector2 const add { 0.0f, 0.0f };

    EXPECT_EQ(initial, initial - add);
}

TEST(VectorAdd, SubtractReal)
{
    jt::Vector2 const initial { 5.0f, -1.245f };
    jt::Vector2 const add { 1.0f, 1.0f };
    jt::Vector2 const expected { initial.x() - add.x(), initial.y() - add.y() };

    EXPECT_EQ(initial - add, expected);
}

TEST(VectorSubEQ, AddZero)
{
    jt::Vector2 const initial { 5.0f, -1.245f };
    jt::Vector2 copy { initial };
    jt::Vector2 const add { 0.0f, 0.0f };
    copy -= add;
    EXPECT_EQ(copy, initial);
}

TEST(VectorSubEQ, AddReal)
{
    jt::Vector2 initial { 5.0f, -1.245f };
    jt::Vector2 const add { 1.0f, -1.0f };
    jt::Vector2 const expected { initial.x() - add.x(), initial.y() - add.y() };
    initial -= add;
    EXPECT_EQ(initial.x(), expected.x());
    EXPECT_EQ(initial.y(), expected.y());
}

TEST(VectorMultiply, One)
{
    jt::Vector2 const initial { 4.2f, 1.1111f };
    EXPECT_EQ(initial * 1.0f, initial);
}

TEST(VectorMultiply, Real)
{
    jt::Vector2 const initial { 4.2f, 1.1111f };
    float const v = 2.5f;
    jt::Vector2 const expected { initial.x() * v, initial.y() * v };
    EXPECT_EQ(initial * v, expected);
}

TEST(VectorDivide, One)
{
    jt::Vector2 const initial { 4.2f, 1.1111f };
    EXPECT_EQ(initial / 1.0f, initial);
}

TEST(VectorDivide, Real)
{
    jt::Vector2 const initial { 4.2f, 1.1111f };
    float const v = 2.5f;
    jt::Vector2 const expected { initial.x() / v, initial.y() / v };
    EXPECT_EQ(initial / v, expected);
}

TEST(Vector2UAccess, ReadAccess)
{
    unsigned int const x { 1 };
    unsigned int const y { 7 };
    jt::Vector2u const v { x, y };
    EXPECT_EQ(v.x(), x);
    EXPECT_EQ(v.y(), y);
}

TEST(Vector2UAccess, WriteAccess)
{
    jt::Vector2u v {};
    unsigned int const x { 5 };
    unsigned int const y { 2 };

    v.x() = x;
    v.y() = y;

    EXPECT_EQ(v.x(), x);
    EXPECT_EQ(v.y(), y);
}

TEST(Vector2U, AddZero)
{
    jt::Vector2u const v { 5, 1 };
    jt::Vector2u const w { 0, 0 };

    EXPECT_EQ(v, v + w);
}
TEST(Vector2U, AddOne)
{
    jt::Vector2u const v { 5, 1 };
    jt::Vector2u const w { 1, 1 };
    jt::Vector2u const expected { v.x() + w.x(), v.y() + w.y() };

    EXPECT_EQ(v + w, expected);
}

TEST(Vector2U, SubtractZero)
{
    jt::Vector2u const v { 5, 1 };
    jt::Vector2u const w { 0, 0 };

    EXPECT_EQ(v, v - w);
}

TEST(Vector2U, SubtractOne)
{
    jt::Vector2u const v { 5, 1 };
    jt::Vector2u const w { 1, 1 };
    jt::Vector2u const expected { v.x() - w.x(), v.y() - w.y() };

    EXPECT_EQ(v - w, expected);
}

TEST(Vector2U, NotEqual)
{
    jt::Vector2u const v { 5, 4 };
    jt::Vector2u const w { 2, 2 };

    EXPECT_NE(v, w);
}
