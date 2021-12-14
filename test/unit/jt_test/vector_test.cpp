#include "vector.hpp"
#include <gtest/gtest.h>

TEST(Vector2fTest, DefaultValues)
{
    jt::Vector2f vec;
    ASSERT_EQ(vec.x, 0.0f);
    ASSERT_EQ(vec.y, 0.0f);
}

TEST(Vector2fTest, Equal)
{
    jt::Vector2f const initial { 5.0f, -1.245f };
    jt::Vector2f const initial2 { initial };

    ASSERT_TRUE(initial == initial2);
    ASSERT_FALSE(initial != initial2);
}

TEST(Vector2fTest, NotEqual)
{
    jt::Vector2f const initial { 5.0f, -1.245f };
    jt::Vector2f const add { 0.0f, 0.0f };

    ASSERT_FALSE(initial == add);
    ASSERT_TRUE(initial != add);
}

TEST(Vector2fTest, AddZereo)
{
    jt::Vector2f const initial { 5.0f, -1.245f };
    jt::Vector2f const add { 0.0f, 0.0f };

    ASSERT_EQ(initial, initial + add);
}

TEST(Vector2fTest, AddReal)
{
    jt::Vector2f const initial { 5.0f, -1.245f };
    jt::Vector2f const add { 1.0f, 1.0f };
    jt::Vector2f const expected { initial.x + add.x, initial.y + add.y };

    ASSERT_EQ(initial + add, expected);
}

TEST(Vector2fTest, AddEQZero)
{
    jt::Vector2f const initial { 5.0f, -1.245f };
    jt::Vector2f copy { initial };
    jt::Vector2f const add { 0.0f, 0.0f };
    copy += add;
    ASSERT_EQ(copy, initial);
}

TEST(Vector2fTest, AddEQReal)
{
    jt::Vector2f initial { 5.0f, -1.245f };
    jt::Vector2f const add { 1.0f, -1.0f };
    jt::Vector2f const expected { initial.x + add.x, initial.y + add.y };
    initial += add;
    ASSERT_EQ(initial, expected);
}

TEST(Vector2fTest, SubtractZereo)
{
    jt::Vector2f const initial { 5.0f, -1.245f };
    jt::Vector2f const add { 0.0f, 0.0f };

    ASSERT_EQ(initial, initial - add);
}

TEST(Vector2fTest, SubtractReal)
{
    jt::Vector2f const initial { 5.0f, -1.245f };
    jt::Vector2f const add { 1.0f, 1.0f };
    jt::Vector2f const expected { initial.x - add.x, initial.y - add.y };

    ASSERT_EQ(initial - add, expected);
}

TEST(Vector2fTest, SubEQZero)
{
    jt::Vector2f const initial { 5.0f, -1.245f };
    jt::Vector2f copy { initial };
    jt::Vector2f const add { 0.0f, 0.0f };
    copy -= add;
    ASSERT_EQ(copy, initial);
}

TEST(Vector2fTest, SubEQReal)
{
    jt::Vector2f initial { 5.0f, -1.245f };
    jt::Vector2f const add { 1.0f, -1.0f };
    jt::Vector2f const expected { initial.x - add.x, initial.y - add.y };
    initial -= add;
    ASSERT_EQ(initial.x, expected.x);
    ASSERT_EQ(initial.y, expected.y);
}

TEST(Vector2fTest, MultiplyOne)
{
    jt::Vector2f const initial { 4.2f, 1.1111f };
    ASSERT_EQ(initial * 1.0f, initial);
}

TEST(Vector2fTest, MultiplyReal)
{
    jt::Vector2f const initial { 4.2f, 1.1111f };
    float const v = 2.5f;
    jt::Vector2f const expected { initial.x * v, initial.y * v };
    ASSERT_EQ(initial * v, expected);
}

TEST(Vector2fTest, DivideOne)
{
    jt::Vector2f const initial { 4.2f, 1.1111f };
    ASSERT_EQ(initial / 1.0f, initial);
}

TEST(Vector2fTest, DivideReal)
{
    jt::Vector2f const initial { 4.2f, 1.1111f };
    float const v = 2.5f;
    jt::Vector2f const expected { initial.x / v, initial.y / v };
    ASSERT_EQ(initial / v, expected);
}

TEST(Vector2UAccess, ReadAccess)
{
    unsigned int const x { 1 };
    unsigned int const y { 7 };
    jt::Vector2u const v { x, y };
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
}

TEST(Vector2UAccess, WriteAccess)
{
    jt::Vector2u v {};
    unsigned int const x { 5 };
    unsigned int const y { 2 };

    v.x = x;
    v.y = y;

    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
}

TEST(Vector2U, AddZero)
{
    jt::Vector2u const v { 5, 1 };
    jt::Vector2u const w { 0, 0 };

    ASSERT_EQ(v, v + w);
}
TEST(Vector2U, AddOne)
{
    jt::Vector2u const v { 5, 1 };
    jt::Vector2u const w { 1, 1 };
    jt::Vector2u const expected { v.x + w.x, v.y + w.y };

    ASSERT_EQ(v + w, expected);
}

TEST(Vector2U, SubtractZero)
{
    jt::Vector2u const v { 5, 1 };
    jt::Vector2u const w { 0, 0 };

    ASSERT_EQ(v, v - w);
}

TEST(Vector2U, SubtractOne)
{
    jt::Vector2u const v { 5, 1 };
    jt::Vector2u const w { 1, 1 };
    jt::Vector2u const expected { v.x - w.x, v.y - w.y };

    ASSERT_EQ(v - w, expected);
}

TEST(Vector2U, NotEqual)
{
    jt::Vector2u const v { 5, 4 };
    jt::Vector2u const w { 2, 2 };

    ASSERT_NE(v, w);
}

TEST(Vector2U, MoveConstructor)
{
    jt::Vector2u vec1 { 2, 3 };
    jt::Vector2u vec2 { std::move(vec1) };

    ASSERT_EQ(vec2.x, 2);
    ASSERT_EQ(vec2.y, 3);
}

TEST(Vector2UAddEqual, AddZero)
{
    jt::Vector2u const initial { 5, 1 };
    jt::Vector2u copy { initial };
    jt::Vector2u const add { 0, 0 };
    copy += add;
    ASSERT_EQ(copy, initial);
}

TEST(Vector2UAddEqual, AddReal)
{
    jt::Vector2u initial { 5, 1 };
    jt::Vector2u const add { 1, 2 };
    jt::Vector2u const expected { initial.x + add.x, initial.y + add.y };
    initial += add;
    ASSERT_EQ(initial, expected);
}

TEST(Vector2UAddEqual, SubtractZero)
{
    jt::Vector2u const initial { 5, 1 };
    jt::Vector2u copy { initial };
    jt::Vector2u const sub { 0, 0 };
    copy -= sub;
    ASSERT_EQ(copy, initial);
}

TEST(Vector2UAddEqual, SubtractReal)
{
    jt::Vector2u initial { 5, 1 };
    jt::Vector2u const sub { 1, 2 };
    jt::Vector2u const expected { initial.x - sub.x, initial.y - sub.y };
    initial -= sub;
    ASSERT_EQ(initial, expected);
}
