#include <vector_lib.hpp>
#include <gtest/gtest.h>

TEST(SFMLVectorLibTest, Vector2fToLib)
{
    auto const x = -23.2f;
    auto const y = 15.0f;
    jt::Vector2f const initialValue { x, y };
    sf::Vector2f const expectedSFVector { x, y };

    auto const converted = jt::toLib(initialValue);

    ASSERT_EQ(converted, expectedSFVector);
}

TEST(SFMLVectorLibTest, Vector2uToLib)
{
    auto const x = 1u;
    auto const y = 15u;
    jt::Vector2u const initialValue { x, y };
    sf::Vector2u const expectedSFVector { x, y };

    auto const converted = jt::toLib(initialValue);

    ASSERT_EQ(converted, expectedSFVector);
}

TEST(SFMLVectorLibTest, Vector2fFromLib)
{
    auto const x = -23.2f;
    auto const y = 15.0f;
    sf::Vector2f const initialValue { x, y };
    jt::Vector2f const expectedJTVector { x, y };

    auto const converted = jt::fromLib(initialValue);

    ASSERT_EQ(converted, expectedJTVector);
}

TEST(SFMLVectorLibTest, Vector2FromLib)
{
    auto const x = 13u;
    auto const y = 1u;
    sf::Vector2u const initialValue { x, y };
    jt::Vector2u const expectedJTVector { x, y };

    auto const converted = jt::fromLib(initialValue);

    ASSERT_EQ(converted, expectedJTVector);
}
