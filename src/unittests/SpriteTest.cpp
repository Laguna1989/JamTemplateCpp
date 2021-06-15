#include "sprite.hpp"
#include <gtest/gtest.h>

TEST(SpriteTest, SpriteCanBeDefaultConstructed)
{
    jt::Sprite s;
    SUCCEED();
}

TEST(SpriteTest, LoadFullSprite)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png");
    EXPECT_FLOAT_EQ(s.getLocalBounds().width(), 192.0f);
    EXPECT_FLOAT_EQ(s.getLocalBounds().height(), 16.0f);
}

TEST(SpriteTest, LoadPartOfSpriteSprite)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png", jt::Recti { 0, 0, 16, 16 });
    EXPECT_FLOAT_EQ(s.getLocalBounds().width(), 16.0f);
    EXPECT_FLOAT_EQ(s.getLocalBounds().height(), 16.0f);
}

TEST(SpriteTest, InitialPosition)
{
    jt::Sprite s;
    EXPECT_FLOAT_EQ(s.getPosition().x(), 0.0f);
    EXPECT_FLOAT_EQ(s.getPosition().y(), 0.0f);
}

TEST(SpriteTest, PositionAfterSetPosition)
{
    jt::Sprite s;
    jt::Vector2 newPos { 200.0f, 150.0f };
    s.setPosition(newPos);
    EXPECT_EQ(s.getPosition(), newPos);
}

TEST(SpriteTest, InitialColor)
{
    jt::Sprite s;
    EXPECT_EQ(s.getColor(), jt::colors::White);
}

TEST(SpriteTest, ColorAfterSetColor)
{
    jt::Sprite s;
    jt::Color newCol { jt::colors::Blue };
    s.setColor(newCol);
    EXPECT_EQ(s.getColor(), newCol);
}

TEST(SpriteTest, InitialFlashColor)
{
    jt::Sprite s;
    EXPECT_EQ(s.getFlashColor(), jt::colors::White);
}

TEST(SpriteTest, FlashColorAfterSetFlashColor)
{
    jt::Sprite s;
    jt::Color newCol { jt::colors::Blue };
    s.setFlashColor(newCol);
    EXPECT_EQ(s.getFlashColor(), newCol);
}

TEST(SpriteTest, InitialLocalBounds)
{
    jt::Sprite s;
    jt::Rect expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    EXPECT_EQ(s.getLocalBounds(), expectedBounds);
}

TEST(SpriteTest, InitialGlobalBounds)
{
    jt::Sprite s;
    jt::Rect expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    EXPECT_EQ(s.getGlobalBounds(), expectedBounds);
}

TEST(SpriteTest, LocalBoundsWithLoadedSprite)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png", jt::Recti { 0, 0, 16, 16 });
    jt::Rect expectedBounds { 0.0f, 0.0f, 16.0f, 16.0f };
    EXPECT_EQ(s.getLocalBounds(), expectedBounds);
}

TEST(SpriteTest, GlobalBoundsWithLoadedSprite)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png", jt::Recti { 0, 0, 16, 16 });
    jt::Rect expectedBounds { 0.0f, 0.0f, 16.0f, 16.0f };
    EXPECT_EQ(s.getGlobalBounds(), expectedBounds);
}

TEST(SpriteTest, InitialScale)
{
    jt::Sprite s;
    EXPECT_FLOAT_EQ(s.getScale().x(), 1.0f);
    EXPECT_FLOAT_EQ(s.getScale().y(), 1.0f);
}

TEST(SpriteTest, ScaleAfterSetScale)
{
    jt::Sprite s;
    jt::Vector2 newScale { 200.0f, 150.0f };
    s.setScale(newScale);
    EXPECT_EQ(s.getScale(), newScale);
}

TEST(SpriteTest, InitialOrigin)
{
    jt::Sprite s;
    EXPECT_FLOAT_EQ(s.getOrigin().x(), 0.0f);
    EXPECT_FLOAT_EQ(s.getOrigin().y(), 0.0f);
}

TEST(SpriteTest, OriginAfterSetOrigin)
{
    jt::Sprite s;
    jt::Vector2 newOrigin { 20.0f, -15.0f };
    s.setOrigin(newOrigin);
    EXPECT_EQ(s.getOrigin(), newOrigin);
}

TEST(SpriteTest, GetPixelOfSprite)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png", jt::Recti { 0, 0, 16, 16 });
    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 0, 0 }), jt::colors::Transparent);
    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 1, 0 }), jt::colors::Transparent);
    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 2, 0 }), jt::colors::Transparent);
    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 3, 0 }), jt::colors::Transparent);
    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 4, 0 }), jt::colors::Transparent);

    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 5, 0 }), jt::colors::Black);
    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 6, 0 }), jt::colors::Black);
    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 7, 0 }), jt::colors::Black);
    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 8, 0 }), jt::colors::Black);
    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 9, 0 }), jt::colors::Black);
    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 10, 0 }), jt::colors::Black);

    jt::Color const expected { 211, 172, 99, 255 };
    EXPECT_EQ(s.getColorAtPixel(jt::Vector2u { 5, 5 }), expected);
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

TEST(SpriteTest, Update)
{
    jt::Sprite s;
    s.update(0.1f);
    SUCCEED();
}

TEST(SpriteTest, DrawNullptr)
{
    jt::Sprite s;
    s.update(0.0f);
    s.draw(nullptr);
    SUCCEED();
}

TEST(SpriteTest, InitialRotation)
{
    jt::Sprite s;
    EXPECT_FLOAT_EQ(s.getRotation(), 0.0f);
}

TEST(SpriteTest, RotationAfterSetRotation)
{
    jt::Sprite s;
    float const expectedRotation { 45.0f };
    s.setRotation(expectedRotation);
    EXPECT_FLOAT_EQ(s.getRotation(), expectedRotation);
}

#if ENABLE_WEB

#else
TEST(SpriteTest, LoadSpriteFromTexture)
{
    sf::Texture t;
    t.create(20U, 20U);
    jt::Sprite s;
    s.fromTexture(t);
    EXPECT_FLOAT_EQ(s.getLocalBounds().width(), 20.0f);
    EXPECT_FLOAT_EQ(s.getLocalBounds().height(), 20.0f);
}

TEST(SpriteTest, GetSfSprite)
{
    jt::Sprite s;
    s.loadSprite("assets/coin.png");

    sf::Sprite value = s.getSFSprite();
    EXPECT_EQ(value.getLocalBounds().left, s.getLocalBounds().left());
    EXPECT_EQ(value.getLocalBounds().top, s.getLocalBounds().top());
    EXPECT_EQ(value.getLocalBounds().width, s.getLocalBounds().width());
    EXPECT_EQ(value.getLocalBounds().height, s.getLocalBounds().height());
}

#if ENABLE_DISPLAY_TESTS
TEST(SpriteTest, GetPixelOutOfBounds)
{
    testing::FLAGS_gtest_death_test_style = "threadsafe";
    jt::Sprite s;
    s.loadSprite("assets/coin.png", jt::Recti { 0, 0, 16, 16 });

    EXPECT_DEATH(s.getColorAtPixel(jt::Vector2u { 22, 25 }), "");
}
#endif

#endif
