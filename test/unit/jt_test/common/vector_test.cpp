#include <vector.hpp>
#include <gtest/gtest.h>
#include <type_traits>

TEST(Vector2fTest, CanBeDefaultConstructed)
{
    static_assert(
        std::is_default_constructible_v<jt::Vector2f>, "Vector2f is not default constructible");
}

TEST(Vector2fTest, CanBeConstructedWithTwoArguments)
{
    static_assert(std::is_constructible_v<jt::Vector2f, float, float>,
        "Vector2f is not constructible from two floats");
}

TEST(Vector2fTest, CanNotBeConstructedWithOneArguments)
{
    static_assert(
        !std::is_constructible_v<jt::Vector2f, float>, "Vector2f is constructible from one float");
}

TEST(Vector2fTest, IsConstexpr) { constexpr jt::Vector2f vec { 15.0f, -2.0f }; }

TEST(Vector2fTest, DefaultValues)
{
    constexpr jt::Vector2f vec;
    ASSERT_EQ(vec.x, 0.0f);
    ASSERT_EQ(vec.y, 0.0f);
}

TEST(Vector2fTest, Equal)
{
    constexpr jt::Vector2f initial { 5.0f, -1.245f };
    constexpr jt::Vector2f initial2 { initial };

    ASSERT_TRUE(initial == initial2);
    ASSERT_FALSE(initial != initial2);
}

TEST(Vector2fTest, NotEqual)
{
    constexpr jt::Vector2f initial { 5.0f, -1.245f };
    constexpr jt::Vector2f add { 0.0f, 0.0f };

    ASSERT_FALSE(initial == add);
    ASSERT_TRUE(initial != add);
}

TEST(Vector2fTest, AddZereo)
{
    constexpr jt::Vector2f initial { 5.0f, -1.245f };
    constexpr jt::Vector2f add { 0.0f, 0.0f };

    ASSERT_EQ(initial, initial + add);
}

TEST(Vector2fTest, AddReal)
{
    constexpr jt::Vector2f initial { 5.0f, -1.245f };
    constexpr jt::Vector2f add { 1.0f, 1.0f };
    constexpr jt::Vector2f expected { initial.x + add.x, initial.y + add.y };

    ASSERT_EQ(initial + add, expected);
}

TEST(Vector2fTest, AddEQZero)
{
    constexpr jt::Vector2f initial { 5.0f, -1.245f };
    constexpr jt::Vector2f add { 0.0f, 0.0f };
    jt::Vector2f copy { initial };

    copy += add;
    ASSERT_EQ(copy, initial);
}

TEST(Vector2fTest, AddEQReal)
{
    jt::Vector2f initial { 5.0f, -1.245f };
    constexpr jt::Vector2f add { 1.0f, -1.0f };
    jt::Vector2f expected { initial.x + add.x, initial.y + add.y };
    initial += add;
    ASSERT_EQ(initial, expected);
}

TEST(Vector2fTest, SubtractZereo)
{
    constexpr jt::Vector2f initial { 5.0f, -1.245f };
    constexpr jt::Vector2f add { 0.0f, 0.0f };

    ASSERT_EQ(initial, initial - add);
}

TEST(Vector2fTest, SubtractReal)
{
    constexpr jt::Vector2f initial { 5.0f, -1.245f };
    constexpr jt::Vector2f add { 1.0f, 1.0f };
    constexpr jt::Vector2f expected { initial.x - add.x, initial.y - add.y };

    ASSERT_EQ(initial - add, expected);
}

TEST(Vector2fTest, SubEQZero)
{
    constexpr jt::Vector2f initial { 5.0f, -1.245f };
    jt::Vector2f copy { initial };
    constexpr jt::Vector2f add { 0.0f, 0.0f };
    copy -= add;
    ASSERT_EQ(copy, initial);
}

TEST(Vector2fTest, SubEQReal)
{
    jt::Vector2f initial { 5.0f, -1.245f };
    constexpr jt::Vector2f add { 1.0f, -1.0f };
    jt::Vector2f expected { initial.x - add.x, initial.y - add.y };
    initial -= add;
    ASSERT_EQ(initial.x, expected.x);
    ASSERT_EQ(initial.y, expected.y);
}

TEST(Vector2fTest, MultiplyOne)
{
    constexpr jt::Vector2f initial { 4.2f, 1.1111f };
    ASSERT_EQ(initial * 1.0f, initial);
}

TEST(Vector2fTest, MultiplyReal)
{
    constexpr jt::Vector2f initial { 4.2f, 1.1111f };
    constexpr float v = 2.5f;
    constexpr jt::Vector2f expected { initial.x * v, initial.y * v };
    ASSERT_EQ(initial * v, expected);
}

TEST(Vector2fTest, DivideOneResultsInSameVector)
{
    constexpr jt::Vector2f initial { 4.2f, 1.1111f };
    ASSERT_EQ(initial / 1.0f, initial);
}

TEST(Vector2fTest, DivideReal)
{
    constexpr jt::Vector2f initial { 4.2f, 1.1111f };
    constexpr float v = 2.5f;
    constexpr jt::Vector2f expected { initial.x / v, initial.y / v };
    ASSERT_EQ(initial / v, expected);
}

TEST(Vector2uTest, CanBeDefaultConstructed)
{
    static_assert(
        std::is_default_constructible_v<jt::Vector2u>, "Vector2u is not default constructible");
}

TEST(Vector2uTest, CanBeConstructedWithTwoArguments)
{
    static_assert(std::is_constructible_v<jt::Vector2u, unsigned int, unsigned int>,
        "Vector2u is not constructible from two unsigned ints");
}

TEST(Vector2uTest, CanNotBeConstructedWithOneArguments)
{
    static_assert(!std::is_constructible_v<jt::Vector2u, unsigned int>,
        "Vector2u is constructible from one unsigned int");
}

TEST(Vector2UAccess, ReadAccess)
{
    constexpr unsigned int x { 1 };
    constexpr unsigned int y { 7 };
    constexpr jt::Vector2u v { x, y };
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
}

TEST(Vector2U, AddZero)
{
    constexpr jt::Vector2u v { 5, 1 };
    constexpr jt::Vector2u w { 0, 0 };
    constexpr auto result = v + w;
    ASSERT_EQ(v, result);
}

TEST(Vector2U, AddOne)
{
    constexpr jt::Vector2u v { 5, 1 };
    constexpr jt::Vector2u w { 1, 1 };
    constexpr jt::Vector2u expected { v.x + w.x, v.y + w.y };

    ASSERT_EQ(v + w, expected);
}

TEST(Vector2U, SubtractZero)
{
    constexpr jt::Vector2u v { 5, 1 };
    constexpr jt::Vector2u w { 0, 0 };
    constexpr auto result = v - w;
    ASSERT_EQ(v, result);
}

TEST(Vector2U, SubtractOne)
{
    constexpr jt::Vector2u v { 5, 1 };
    constexpr jt::Vector2u w { 1, 1 };
    constexpr jt::Vector2u expected { v.x - w.x, v.y - w.y };
    constexpr auto result = v - w;

    ASSERT_EQ(result, expected);
}

TEST(Vector2U, NotEqual)
{
    constexpr jt::Vector2u v { 5, 4 };
    constexpr jt::Vector2u w { 2, 2 };

    ASSERT_NE(v, w);
}

TEST(Vector2U, MoveConstructor)
{
    constexpr jt::Vector2u vec1 { 2, 3 };
    constexpr jt::Vector2u vec2 { std::move(vec1) };

    ASSERT_EQ(vec2.x, 2);
    ASSERT_EQ(vec2.y, 3);
}

TEST(Vector2UAddEqual, AddZero)
{
    constexpr jt::Vector2u initial { 5, 1 };
    jt::Vector2u copy { initial };
    constexpr jt::Vector2u add { 0, 0 };
    copy += add;
    ASSERT_EQ(copy, initial);
}

TEST(Vector2UAddEqual, AddReal)
{
    jt::Vector2u initial { 5, 1 };
    constexpr jt::Vector2u add { 1, 2 };
    jt::Vector2u const expected { initial.x + add.x, initial.y + add.y };
    initial += add;
    ASSERT_EQ(initial, expected);
}

TEST(Vector2UAddEqual, SubtractZero)
{
    constexpr jt::Vector2u initial { 5, 1 };
    jt::Vector2u copy { initial };
    constexpr jt::Vector2u sub { 0, 0 };
    copy -= sub;
    ASSERT_EQ(copy, initial);
}

TEST(Vector2UAddEqual, SubtractReal)
{
    jt::Vector2u initial { 5, 1 };
    constexpr jt::Vector2u sub { 1, 2 };
    jt::Vector2u const expected { initial.x - sub.x, initial.y - sub.y };
    initial -= sub;
    ASSERT_EQ(initial, expected);
}
