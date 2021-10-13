#include "shape.hpp"
#include <gtest/gtest.h>

TEST(ShapeTest, ShapeCanBeDefaultConstructed)
{
    jt::Shape s;
    SUCCEED();
}

TEST(ShapeTest, MakeRect)
{
    jt::Shape s;
    s.makeRect(jt::Vector2 { 50, 50 });
    SUCCEED();
}

TEST(ShapeTest, InitialPosition)
{
    jt::Shape s;
    EXPECT_FLOAT_EQ(s.getPosition().x(), 0.0f);
    EXPECT_FLOAT_EQ(s.getPosition().y(), 0.0f);
}

TEST(ShapeTest, PositionAfterSetPosition)
{
    jt::Shape s;
    jt::Vector2 newPos { 200.0f, 150.0f };
    s.setPosition(newPos);
    EXPECT_EQ(s.getPosition(), newPos);
}

TEST(ShapeTest, InitialColor)
{
    jt::Shape s;
    s.makeRect({ 25, 30 });
    EXPECT_EQ(s.getColor(), jt::colors::White);
}

TEST(ShapeTest, ColorAfterSetColor)
{
    jt::Shape s;
    s.makeRect({ 25, 30 });
    jt::Color newCol { jt::colors::Blue };
    s.setColor(newCol);
    EXPECT_EQ(s.getColor(), newCol);
}

TEST(ShapeTest, InitialFlashColor)
{
    jt::Shape s;
    s.makeRect({ 25, 30 });
    EXPECT_EQ(s.getFlashColor(), jt::colors::White);
}

TEST(ShapeTest, FlashColorAfterSetFlashColor)
{
    jt::Shape s;
    s.makeRect({ 25, 30 });
    jt::Color newCol { jt::colors::Blue };
    s.setFlashColor(newCol);
    EXPECT_EQ(s.getFlashColor(), newCol);
}

TEST(ShapeTest, InitialLocalBounds)
{
    jt::Shape s;

    jt::Rect expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    EXPECT_EQ(s.getLocalBounds(), expectedBounds);
}

TEST(ShapeTest, InitialGlobalBounds)
{
    jt::Shape s;
    jt::Rect expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    EXPECT_EQ(s.getGlobalBounds(), expectedBounds);
}

TEST(ShapeTest, LocalBoundsWithRectShape)
{
    jt::Shape s;
    s.makeRect(jt::Vector2 { 50.0f, 50.0f });
    jt::Rect expectedBounds { 0.0f, 0.0f, 50.0f, 50.0f };
    EXPECT_EQ(s.getLocalBounds(), expectedBounds);
}

TEST(ShapeTest, GlobalBoundsWithLoadedShape)
{
    jt::Shape s;
    s.makeRect(jt::Vector2 { 16.0f, 16.0f });
    jt::Rect expectedBounds { 0.0f, 0.0f, 16.0f, 16.0f };
    EXPECT_EQ(s.getGlobalBounds(), expectedBounds);
}

TEST(ShapeTest, InitialScale)
{
    jt::Shape s;
    EXPECT_FLOAT_EQ(s.getScale().x(), 1.0f);
    EXPECT_FLOAT_EQ(s.getScale().y(), 1.0f);
}

TEST(ShapeTest, ScaleAfterSetScale)
{
    jt::Shape s;
    s.makeRect({ 500, 500 });
    jt::Vector2 newScale { 200.0f, 150.0f };
    s.setScale(newScale);
    EXPECT_EQ(s.getScale(), newScale);
}

TEST(ShapeTest, InitialOrigin)
{
    jt::Shape s;
    EXPECT_FLOAT_EQ(s.getOrigin().x(), 0.0f);
    EXPECT_FLOAT_EQ(s.getOrigin().y(), 0.0f);
}

TEST(ShapeTest, OriginAfterSetOrigin)
{
    jt::Shape s;
    s.makeRect({ 5, 5 });
    jt::Vector2 newOrigin { 20.0f, -15.0f };
    s.setOrigin(newOrigin);
    EXPECT_EQ(s.getOrigin(), newOrigin);
}

TEST(ShapeTest, Update)
{
    jt::Shape s;
    s.update(0.1f);
    SUCCEED();
}

TEST(ShapeTest, DrawNullptr)
{
    jt::Shape s;
    s.update(0.0f);
    s.draw(nullptr);
    SUCCEED();
}

TEST(ShapeTest, InitialRotation)
{
    jt::Shape s;
    EXPECT_FLOAT_EQ(s.getRotation(), 0.0f);
}

TEST(ShapeTest, RotationAfterSetRotation)
{
    jt::Shape s;
    float const expectedRotation { 45.0f };
    s.setRotation(expectedRotation);
    EXPECT_FLOAT_EQ(s.getRotation(), expectedRotation);
}

TEST(ShapeTest, GlobalBoundsWithOffset)
{
    jt::Shape s;
    s.makeRect(jt::Vector2 { 100.0f, 100.0f });
    s.setOffset(jt::Vector2 { -30.0f, -50.0f });
    s.update(0.1f);
    auto bounds = s.getGlobalBounds();
    jt::Rect const expectedBounds { -30.0f, -50.0f, 100.0f, 100.0f };
    ASSERT_EQ(bounds, expectedBounds);
}
