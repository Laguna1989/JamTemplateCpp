#include "text.hpp"
#include <gtest/gtest.h>

namespace {
jt::Text getText()
{
    jt::Text t;
    std::shared_ptr<jt::renderTarget> rt { nullptr };
    t.loadFont("assets/font.ttf", 20, rt);
    return t;
};
} // namespace

TEST(TextTest, InitialValues)
{
    jt::Text t = getText();
    EXPECT_FLOAT_EQ(t.getLocalBounds().width(), 0.0f);
    EXPECT_FLOAT_EQ(t.getLocalBounds().height(), 0.0f);
}
TEST(TextTest, Destructor)
{
    {
        jt::Text t;
    }
}

TEST(TextTest, LoadFont)
{
    jt::Text t = getText();
    SUCCEED();
}

TEST(TextTest, SetText)
{
    jt::Text t = getText();
    t.setText("test1234");
    EXPECT_EQ(t.getText(), "test1234");
}

TEST(TextTest, LoadInvalidFont)
{
    jt::Text t;
    std::shared_ptr<jt::renderTarget> rt { nullptr };
    t.loadFont("assets/font_INVALID_.ttf", 20, rt);
    SUCCEED();
}

TEST(TextTest, InitialPosition)
{
    jt::Text t = getText();
    EXPECT_FLOAT_EQ(t.getPosition().x(), 0.0f);
    EXPECT_FLOAT_EQ(t.getPosition().y(), 0.0f);
}

TEST(TextTest, PositionAfterSetPosition)
{
    jt::Text t = getText();
    jt::Vector2 newPos { 200.0f, 150.0f };
    t.setPosition(newPos);
    EXPECT_EQ(t.getPosition(), newPos);
}

TEST(TextTest, InitialColor)
{
    jt::Text t = getText();
    EXPECT_EQ(t.getColor(), jt::colors::White);
}

TEST(TextTest, ColorAfterSetColor)
{
    jt::Text t = getText();
    jt::Color newCol { jt::colors::Blue };
    t.setColor(newCol);
    EXPECT_EQ(t.getColor(), newCol);
}

TEST(TextTest, InitialFlashColor)
{
    jt::Text t = getText();
    EXPECT_EQ(t.getFlashColor(), jt::colors::White);
}

TEST(TextTest, FlashColorAfterSetFlashColor)
{
    jt::Text t = getText();
    jt::Color newCol { jt::colors::Blue };
    t.setFlashColor(newCol);
    EXPECT_EQ(t.getFlashColor(), newCol);
}

TEST(TextTest, InitialLocalBounds)
{
    jt::Text t = getText();
    jt::Rect expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    EXPECT_EQ(t.getLocalBounds(), expectedBounds);
}

TEST(TextTest, InitialGlobalBounds)
{
    jt::Text t = getText();
    jt::Rect expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    EXPECT_EQ(t.getGlobalBounds(), expectedBounds);
}

TEST(TextTest, LocalBoundsWithLoadedSprite)
{
    jt::Text t = getText();
    t.setText("test1234");
    jt::Rect expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    EXPECT_NE(t.getLocalBounds(), expectedBounds);
}

TEST(TextTest, InitialScale)
{
    jt::Text t = getText();
    EXPECT_FLOAT_EQ(t.getScale().x(), 1.0f);
    EXPECT_FLOAT_EQ(t.getScale().y(), 1.0f);
}

TEST(TextTest, ScaleAfterSetScale)
{
    jt::Text t = getText();
    jt::Vector2 newScale { 200.0f, 150.0f };
    t.setScale(newScale);
    EXPECT_EQ(t.getScale(), newScale);
}

TEST(TextTest, InitialOrigin)
{
    jt::Text t = getText();
    EXPECT_FLOAT_EQ(t.getOrigin().x(), 0.0f);
    EXPECT_FLOAT_EQ(t.getOrigin().y(), 0.0f);
}

TEST(TextTest, OriginAfterSetOrigin)
{
    jt::Text t = getText();
    jt::Vector2 newOrigin { 20.0f, -15.0f };
    t.setOrigin(newOrigin);
    EXPECT_EQ(t.getOrigin(), newOrigin);
}

TEST(TextTest, Update)
{
    jt::Text t = getText();
    t.update(0.1f);
    SUCCEED();
}

TEST(TextTest, DrawNullptr)
{
    jt::Text t = getText();
    t.update(0.0f);
    t.draw(nullptr);
    SUCCEED();
}

TEST(TextTest, InitialRotation)
{
    jt::Text t = getText();
    EXPECT_FLOAT_EQ(t.getRotation(), 0.0f);
}

TEST(TextTest, RotationAfterSetRotation)
{
    jt::Text t = getText();
    float const expectedRotation { 45.0f };
    t.setRotation(expectedRotation);
    EXPECT_FLOAT_EQ(t.getRotation(), expectedRotation);
}
