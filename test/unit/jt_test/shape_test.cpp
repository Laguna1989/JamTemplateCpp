#include "sdl_setup.hpp"
#include "shape.hpp"
#include "texture_manager_impl.hpp"
#include <gtest/gtest.h>

class ShapeTestFixture : public ::testing::Test {
public:
    jt::TextureManagerInterface& tm { getTextureManager() };
    jt::Shape s;
};

TEST_F(ShapeTestFixture, ShapeCanBeDefaultConstructed) { SUCCEED(); }

TEST_F(ShapeTestFixture, MakeRect)
{
    s.makeRect(jt::Vector2f { 50, 50 }, tm);
    SUCCEED();
}

TEST_F(ShapeTestFixture, InitialPosition)
{
    EXPECT_FLOAT_EQ(s.getPosition().x, 0.0f);
    EXPECT_FLOAT_EQ(s.getPosition().y, 0.0f);
}

TEST_F(ShapeTestFixture, PositionAfterSetPosition)
{
    jt::Vector2f newPos { 200.0f, 150.0f };
    s.setPosition(newPos);
    EXPECT_EQ(s.getPosition(), newPos);
}

TEST_F(ShapeTestFixture, InitialColor)
{
    s.makeRect({ 25, 30 }, tm);
    EXPECT_EQ(s.getColor(), jt::colors::White);
}

TEST_F(ShapeTestFixture, ColorAfterSetColor)
{
    s.makeRect({ 25, 30 }, tm);
    jt::Color newCol { jt::colors::Blue };
    s.setColor(newCol);
    EXPECT_EQ(s.getColor(), newCol);
}

TEST_F(ShapeTestFixture, InitialFlashColor)
{
    s.makeRect({ 25, 30 }, tm);
    EXPECT_EQ(s.getFlashColor(), jt::colors::White);
}

TEST_F(ShapeTestFixture, FlashColorAfterSetFlashColor)
{
    s.makeRect({ 25, 30 }, tm);
    jt::Color newCol { jt::colors::Blue };
    s.setFlashColor(newCol);
    EXPECT_EQ(s.getFlashColor(), newCol);
}

TEST_F(ShapeTestFixture, InitialLocalBounds)
{
    jt::Rectf expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    EXPECT_EQ(s.getLocalBounds(), expectedBounds);
}

TEST_F(ShapeTestFixture, InitialGlobalBounds)
{
    jt::Rectf expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    EXPECT_EQ(s.getGlobalBounds(), expectedBounds);
}

TEST_F(ShapeTestFixture, LocalBoundsWithRectShape)
{
    s.makeRect(jt::Vector2f { 50.0f, 50.0f }, tm);
    jt::Rectf expectedBounds { 0.0f, 0.0f, 50.0f, 50.0f };
    EXPECT_EQ(s.getLocalBounds(), expectedBounds);
}

TEST_F(ShapeTestFixture, GlobalBoundsWithLoadedShape)
{
    s.makeRect(jt::Vector2f { 16.0f, 16.0f }, tm);
    jt::Rectf expectedBounds { 0.0f, 0.0f, 16.0f, 16.0f };
    EXPECT_EQ(s.getGlobalBounds(), expectedBounds);
}

TEST_F(ShapeTestFixture, InitialScale)
{
    EXPECT_FLOAT_EQ(s.getScale().x, 1.0f);
    EXPECT_FLOAT_EQ(s.getScale().y, 1.0f);
}

TEST_F(ShapeTestFixture, ScaleAfterSetScale)
{
    s.makeRect({ 500, 500 }, tm);
    jt::Vector2f newScale { 200.0f, 150.0f };
    s.setScale(newScale);
    EXPECT_EQ(s.getScale(), newScale);
}

TEST_F(ShapeTestFixture, InitialOrigin)
{
    EXPECT_FLOAT_EQ(s.getOrigin().x, 0.0f);
    EXPECT_FLOAT_EQ(s.getOrigin().y, 0.0f);
}

TEST_F(ShapeTestFixture, OriginAfterSetOrigin)
{
    s.makeRect({ 5, 5 }, tm);
    jt::Vector2f newOrigin { 20.0f, -15.0f };
    s.setOrigin(newOrigin);
    EXPECT_EQ(s.getOrigin(), newOrigin);
}

TEST_F(ShapeTestFixture, Update)
{
    s.update(0.1f);
    SUCCEED();
}

TEST_F(ShapeTestFixture, DrawNullptr)
{
    s.update(0.0f);
    s.draw(nullptr);
    SUCCEED();
}

TEST_F(ShapeTestFixture, InitialRotation) { EXPECT_FLOAT_EQ(s.getRotation(), 0.0f); }

TEST_F(ShapeTestFixture, RotationAfterSetRotation)
{
    float const expectedRotation { 45.0f };
    s.setRotation(expectedRotation);
    EXPECT_FLOAT_EQ(s.getRotation(), expectedRotation);
}

TEST_F(ShapeTestFixture, GlobalBoundsWithOffset)
{
    s.makeRect(jt::Vector2f { 100.0f, 100.0f }, tm);
    s.setOffset(jt::Vector2f { -30.0f, -50.0f });
    s.update(0.1f);
    auto bounds = s.getGlobalBounds();
    jt::Rectf const expectedBounds { -30.0f, -50.0f, 100.0f, 100.0f };
    ASSERT_EQ(bounds, expectedBounds);
}
