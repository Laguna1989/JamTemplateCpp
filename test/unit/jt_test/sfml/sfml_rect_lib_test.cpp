#include <rect_lib.hpp>
#include <gtest/gtest.h>

TEST(SFMLRectLibTest, RectfToLib)
{
    auto const x = -23.2f;
    auto const y = 15.0f;
    auto const w = 3.0f;
    auto const h = 5.0f;
    jt::Rectf const initialValue { x, y, w, h };
    sf::FloatRect const expectedSFRect { x, y, w, h };

    auto const converted = jt::toLib(initialValue);

    ASSERT_EQ(converted, expectedSFRect);
}

TEST(SFMLRectLibTest, RectiToLib)
{
    auto const x = -23;
    auto const y = 15;
    auto const w = 3;
    auto const h = 5;
    jt::Recti const initialValue { x, y, w, h };
    sf::IntRect const expectedSFRect { x, y, w, h };

    auto const converted = jt::toLib(initialValue);

    ASSERT_EQ(converted, expectedSFRect);
}

TEST(SFMLRectLibTest, RectfFromLib)
{
    auto const x = -23.2f;
    auto const y = 15.0f;
    auto const w = 3.0f;
    auto const h = 5.0f;
    sf::FloatRect const initialValue { x, y, w, h };
    jt::Rectf const expectedJTRect { x, y, w, h };

    auto const converted = jt::fromLib(initialValue);

    ASSERT_EQ(converted, expectedJTRect);
}

TEST(SFMLRectLibTest, RectiFromLib)
{
    auto const x = -23;
    auto const y = 15;
    auto const w = 3;
    auto const h = 5;
    sf::IntRect const initialValue { x, y, w, h };
    jt::Recti const expectedJTRect { x, y, w, h };

    auto const converted = jt::fromLib(initialValue);

    ASSERT_EQ(converted, expectedJTRect);
}
