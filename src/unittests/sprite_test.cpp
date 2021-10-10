#include "sprite.hpp"
#include <gtest/gtest.h>
#include <type_traits>

TEST(SpriteTest, SpriteCanBeDefaultConstructed)
{
    ASSERT_TRUE(std::is_default_constructible<jt::Sprite>::value);
}

TEST(SpriteTest, SizeCorrectAfterLoadFullSprite)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png");
    ASSERT_FLOAT_EQ(s.getLocalBounds().width(), 192.0f);
    ASSERT_FLOAT_EQ(s.getLocalBounds().height(), 16.0f);
}

TEST(SpriteTest, SizeCorrecrAfterLoadPartialSprite)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png", jt::Recti { 0, 0, 16, 16 });
    ASSERT_FLOAT_EQ(s.getLocalBounds().width(), 16.0f);
    ASSERT_FLOAT_EQ(s.getLocalBounds().height(), 16.0f);
}

TEST(SpriteTest, InitialLocalBounds)
{
    jt::Sprite s;
    jt::Rect expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    ASSERT_EQ(s.getLocalBounds(), expectedBounds);
}

TEST(SpriteTest, InitialGlobalBounds)
{
    jt::Sprite s;
    jt::Rect expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    ASSERT_EQ(s.getGlobalBounds(), expectedBounds);
}

TEST(SpriteTest, CleanImage)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png", jt::Recti { 0, 0, 16, 16 });
    s.cleanImage();
    SUCCEED();
}

TEST(SpriteTest, CleanImageAfterGetColor)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png", jt::Recti { 0, 0, 16, 16 });
    s.getColorAtPixel(jt::Vector2u { 8, 0 });
    s.cleanImage();
    SUCCEED();
}

class SpriteGetPixelTestFixture
    : public ::testing::TestWithParam<std::pair<jt::Vector2u, jt::Color>> {
};

TEST_P(SpriteGetPixelTestFixture, GetPixel)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png", jt::Recti { 0, 0, 16, 16 });
    auto const pos = GetParam().first;
    auto const expected = GetParam().second;
    auto const result = s.getColorAtPixel(pos);
    ASSERT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(SpriteGetPixelTestBorder, SpriteGetPixelTestFixture,
    ::testing::Values(std::make_pair(jt::Vector2u { 0, 0 }, jt::Color { 0, 0, 0, 0 }),
        std::make_pair(jt::Vector2u { 15, 0 }, jt::Color { 0, 0, 0, 0 }),
        std::make_pair(jt::Vector2u { 0, 15 }, jt::Color { 0, 0, 0, 0 }),
        std::make_pair(jt::Vector2u { 15, 15 }, jt::Color { 0, 0, 0, 0 })));

INSTANTIATE_TEST_SUITE_P(SpriteGetPixelTestCenter, SpriteGetPixelTestFixture,
    ::testing::Values(std::make_pair(jt::Vector2u { 5, 0 }, jt::Color { 0, 0, 0, 255 }),
        std::make_pair(jt::Vector2u { 0, 5 }, jt::Color { 0, 0, 0, 255 }),
        std::make_pair(jt::Vector2u { 7, 7 }, jt::Color { 211, 172, 99, 255 })));

class SpriteGetPixelOutOfBoundsTestFixture : public ::testing::TestWithParam<jt::Vector2u> {
};

TEST_P(SpriteGetPixelOutOfBoundsTestFixture, GetPixelOutOfBounds)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png", jt::Recti { 0, 0, 16, 16 });
    auto const pos = GetParam();
    ASSERT_THROW(s.getColorAtPixel(pos), std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(SpriteGetPixelOutOfBoundsTest, SpriteGetPixelOutOfBoundsTestFixture,
    ::testing::Values(jt::Vector2u { 100, 500 }, jt::Vector2u { 16, 16 }));
