#include "animation.hpp"
#include "bar.hpp"
#include "line.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "text.hpp"
#include "tilemap.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

std::shared_ptr<jt::DrawableInterface> createSprite()
{
    auto s = std::make_shared<jt::Sprite>();
    s->loadSprite("assets/coin.png");
    return s;
}

std::shared_ptr<jt::DrawableInterface> createAnimation()
{
    auto a = std::make_shared<jt::Animation>();
    a->add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 0.1f);
    a->play("idle");
    return a;
}

std::shared_ptr<jt::DrawableInterface> createShape()
{
    auto s = std::make_shared<jt::Shape>();
    s->makeRect(jt::Vector2 { 16, 16 });
    return s;
}

std::shared_ptr<jt::DrawableInterface> createText()
{
    auto t = std::make_shared<jt::Text>();
    std::shared_ptr<jt::renderTarget> rt { nullptr };
    t->loadFont("assets/font.ttf", 12, rt);
    return t;
}

std::shared_ptr<jt::DrawableInterface> createBar()
{
    auto b = std::make_shared<jt::Bar>(32.0f, 12.0f);
    return b;
}

std::shared_ptr<jt::DrawableInterface> createTileMap()
{
    auto t = std::make_shared<jt::Tilemap>("assets/tileson_test.json");
    t->setScreenSizeHint(jt::Vector2 { 400.0f, 300.0f });
    return t;
}

std::shared_ptr<jt::DrawableInterface> createLine()
{
    auto l = std::make_shared<jt::Line>(jt::Vector2 { 1.0f, 10.0f });
    return l;
}


class DrawableImplTestFixture
    : public ::testing::TestWithParam<std::shared_ptr<jt::DrawableInterface>> {
public:
    std::shared_ptr<jt::DrawableInterface> drawable { GetParam() };
};

INSTANTIATE_TEST_SUITE_P(DrawableImplTest, DrawableImplTestFixture,
    ::testing::Values(createSprite(), createAnimation(), createShape(), createText(), createBar(),
        createTileMap(), createLine()));

TEST_P(DrawableImplTestFixture, GlobalBoundsEqualLocalBoundsInitially)
{
    ASSERT_EQ(drawable->getLocalBounds(), drawable->getGlobalBounds());
}

TEST_P(DrawableImplTestFixture, InitialOffset)
{
    jt::Vector2 const expected { 0.0f, 0.0f };
    ASSERT_EQ(drawable->getOffset(), expected);
}

TEST_P(DrawableImplTestFixture, OffsetAfterSetOffset)
{
    jt::Vector2 const expected { -55.0f, 12.5f };
    drawable->setOffset(expected);
    ASSERT_EQ(drawable->getOffset(), expected);
}

TEST_P(DrawableImplTestFixture, InitialOrigin)
{
    jt::Vector2 const expected { 0.0f, 0.0f };
    ASSERT_EQ(drawable->getOrigin(), expected);
}

TEST_P(DrawableImplTestFixture, OriginAfterSetOffset)
{
    jt::Vector2 const expected { -55.0f, 12.5f };
    drawable->setOrigin(expected);
    ASSERT_EQ(drawable->getOrigin(),expected);
}

TEST_P(DrawableImplTestFixture, GetIgnoreCamMovementAfterSet)
{
    drawable->setIgnoreCamMovement(false);
    ASSERT_FALSE(drawable->getIgnoreCamMovement());
}

TEST_P(DrawableImplTestFixture, GetPositionInitial)
{
    jt::Vector2 const expected{0.0f, 0.0f};
    ASSERT_EQ(drawable->getPosition(), expected);
}

TEST_P(DrawableImplTestFixture, GetPositionAfterSetPosition)
{
    jt::Vector2 const expected{55.5f, -12.0f};
    drawable->setPosition(expected);
    ASSERT_EQ(drawable->getPosition(), expected);
}

TEST_P(DrawableImplTestFixture, GetScaleInitial)
{
    jt::Vector2 const expected{1.0f, 1.0f};
    ASSERT_EQ(drawable->getScale(), expected);
}

TEST_P(DrawableImplTestFixture, GetScaleAfterSetScale)
{
    jt::Vector2 const expected{55.5f, -12.0f};
    drawable->setScale(expected);
    ASSERT_EQ(drawable->getScale(), expected);
}

TEST_P(DrawableImplTestFixture, DrawWithoutUpdate)
{
    std::shared_ptr<jt::DrawableInterface> drawable = GetParam();
    auto rt = std::make_shared<jt::renderTarget>();
    drawable->draw(rt);
}

TEST_P(DrawableImplTestFixture, Draw)
{
    std::shared_ptr<jt::DrawableInterface> drawable = GetParam();

    auto rt = std::make_shared<jt::renderTarget>();
    drawable->update(0.1f);
    drawable->draw(rt);
}

TEST_P(DrawableImplTestFixture, DrawWithShadow)
{
    std::shared_ptr<jt::DrawableInterface> drawable = GetParam();
    drawable->setShadow(jt::colors::Green, jt::Vector2 { 4, 4 });
    drawable->update(0.1f);
    auto rt = std::make_shared<jt::renderTarget>();
    drawable->draw(rt);
}

TEST_P(DrawableImplTestFixture, DrawWithSetColor)
{
    std::shared_ptr<jt::DrawableInterface> drawable = GetParam();
    drawable->setColor(jt::colors::Red);
    drawable->update(0.1f);
    auto rt = std::make_shared<jt::renderTarget>();
    drawable->draw(rt);
}

TEST_P(DrawableImplTestFixture, DrawWithFlash)
{
    std::shared_ptr<jt::DrawableInterface> drawable = GetParam();
    drawable->flash(5.0f);
    drawable->update(0.1f);
    auto rt = std::make_shared<jt::renderTarget>();
    drawable->draw(rt);
    drawable->update(5.0f);
    drawable->draw(rt);
}

TEST_P(DrawableImplTestFixture, DrawWithShake)
{
    std::shared_ptr<jt::DrawableInterface> drawable = GetParam();
    drawable->shake(5.0f, 0.02f);
    drawable->update(0.1f);
    auto rt = std::make_shared<jt::renderTarget>();
    drawable->draw(rt);
    drawable->update(5.0f);
    drawable->draw(rt);
}

TEST_P(DrawableImplTestFixture, DrawScaled)
{
    std::shared_ptr<jt::DrawableInterface> drawable = GetParam();
    drawable->setScale(jt::Vector2 { 2.0f, 2.0f });
    drawable->update(0.1f);
    auto rt = std::make_shared<jt::renderTarget>();
    jt::DrawableImpl::setCamOffset(jt::Vector2 { 100.0f, 100.0f });
    drawable->draw(rt);
}

TEST_P(DrawableImplTestFixture, DrawRotated)
{
    std::shared_ptr<jt::DrawableInterface> drawable = GetParam();
    drawable->setOrigin(jt::Vector2 { 16.0f, 16.0f });
    drawable->setRotation(22.5f);
    drawable->update(0.1f);
    auto rt = std::make_shared<jt::renderTarget>();
    jt::DrawableImpl::setCamOffset(jt::Vector2 { 100.0f, 100.0f });
    drawable->draw(rt);
}
