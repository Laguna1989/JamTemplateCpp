#include <backend_setup.hpp>
#include <text.hpp>
#include <gtest/gtest.h>

namespace {

std::shared_ptr<jt::Text> getText()
{
    auto t = std::make_shared<jt::Text>();
#if USE_SFML
    std::shared_ptr<jt::RenderTargetLayer> renderTarget { nullptr };
    t->loadFont("assets/font.ttf", 20, renderTarget);
#else
    static SDLSetup setup;
    t->loadFont("assets/font.ttf", 20, setup.m_renderTarget);
#endif
    return t;
};

} // namespace

TEST(TextTest, InitialValues)
{
    auto t = getText();
    ASSERT_FLOAT_EQ(t->getLocalBounds().width, 0.0f);
    ASSERT_FLOAT_EQ(t->getLocalBounds().height, 0.0f);
}

TEST(TextTest, Destructor)
{
    {
        jt::Text t;
    }
}

TEST(TextTest, LoadFont)
{
    auto t = getText();
    SUCCEED();
}

TEST(TextTest, SetText)
{
    auto t = getText();
    t->setText("test1234");
    ASSERT_EQ(t->getText(), "test1234");
}

TEST(TextTest, LoadInvalidFont)
{
    auto t = std::make_shared<jt::Text>();
    std::shared_ptr<jt::RenderTargetLayer> renderTarget { nullptr };
    ASSERT_NO_THROW(t->loadFont("assets/font_INVALID_.ttf", 20, renderTarget));
}

TEST(TextTest, InitialPosition)
{
    auto t = getText();
    ASSERT_FLOAT_EQ(t->getPosition().x, 0.0f);
    ASSERT_FLOAT_EQ(t->getPosition().y, 0.0f);
}

TEST(TextTest, PositionAfterSetPosition)
{
    auto t = getText();
    jt::Vector2f newPos { 200.0f, 150.0f };
    t->setPosition(newPos);
    ASSERT_EQ(t->getPosition(), newPos);
}

TEST(TextTest, InitialColor)
{
    auto t = getText();
    ASSERT_EQ(t->getColor(), jt::colors::White);
}

TEST(TextTest, ColorAfterSetColor)
{
    auto t = getText();
    jt::Color newCol { jt::colors::Blue };
    t->setColor(newCol);
    ASSERT_EQ(t->getColor(), newCol);
}

TEST(TextTest, InitialFlashColor)
{
    auto t = getText();
    ASSERT_EQ(t->getFlashColor(), jt::colors::White);
}

TEST(TextTest, FlashColorAfterSetFlashColor)
{
    auto t = getText();
    jt::Color newCol { jt::colors::Blue };
    t->setFlashColor(newCol);
    ASSERT_EQ(t->getFlashColor(), newCol);
}

TEST(TextTest, InitialLocalBounds)
{
    auto t = getText();
    jt::Rectf expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    ASSERT_EQ(t->getLocalBounds(), expectedBounds);
}

TEST(TextTest, InitialGlobalBounds)
{
    auto t = getText();
    jt::Rectf expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    ASSERT_EQ(t->getGlobalBounds(), expectedBounds);
}

TEST(TextTest, LocalBoundsWithLoadedText)
{
    auto t = getText();
    t->setText("test1234");
    jt::Rectf expectedBounds { 0.0f, 0.0f, 0.0f, 0.0f };
    ASSERT_NE(t->getLocalBounds(), expectedBounds);
}

TEST(TextTest, InitialScale)
{
    auto t = getText();
    ASSERT_FLOAT_EQ(t->getScale().x, 1.0f);
    ASSERT_FLOAT_EQ(t->getScale().y, 1.0f);
}

TEST(TextTest, ScaleAfterSetScale)
{
    auto t = getText();
    jt::Vector2f newScale { 200.0f, 150.0f };
    t->setScale(newScale);
    ASSERT_EQ(t->getScale(), newScale);
}

TEST(TextTest, InitialOrigin)
{
    auto t = getText();
    ASSERT_FLOAT_EQ(t->getOrigin().x, 0.0f);
    ASSERT_FLOAT_EQ(t->getOrigin().y, 0.0f);
}

TEST(TextTest, OriginAfterSetOrigin)
{
    auto t = getText();
    jt::Vector2f newOrigin { 20.0f, -15.0f };
    t->setOrigin(newOrigin);
    ASSERT_EQ(t->getOrigin(), newOrigin);
}

TEST(TextTest, Update)
{
    auto t = getText();
    ASSERT_NO_THROW(t->update(0.1f));
}

TEST(TextTest, SetOutline)
{
    auto t = getText();
    t->setOutline(jt::colors::Red, 2);
}

TEST(TextTest, InitialRotation)
{
    auto t = getText();
    ASSERT_FLOAT_EQ(t->getRotation(), 0.0f);
}

TEST(TextTest, RotationAfterSetRotation)
{
    auto t = getText();
    float const expectedRotation { 45.0f };
    t->setRotation(expectedRotation);
    ASSERT_FLOAT_EQ(t->getRotation(), expectedRotation);
}

TEST(TextTest, InitialTextAlignDefault)
{
    auto t = getText();
    ASSERT_EQ(t->getTextAlign(), jt::Text::TextAlign::CENTER);
}

TEST(TextTest, TextAlignAfterSetRight)
{
    auto t = getText();
    t->setTextAlign(jt::Text::TextAlign::RIGHT);
    t->update(0.1f);
    ASSERT_EQ(t->getTextAlign(), jt::Text::TextAlign::RIGHT);
}

TEST(TextTest, TextAlignAfterSetLeft)
{
    auto t = getText();
    t->setTextAlign(jt::Text::TextAlign::LEFT);
    t->update(0.1f);
    ASSERT_EQ(t->getTextAlign(), jt::Text::TextAlign::LEFT);
}
