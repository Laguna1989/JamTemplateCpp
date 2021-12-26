#include "drawables_impl_test.hpp"
#include "sdl_setup.hpp"
#include "texture_manager_impl.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

class DrawableImplTestFixture
    : public ::testing::TestWithParam<std::shared_ptr<DrawableFactoryInterface>> {
protected:
    std::shared_ptr<jt::DrawableInterface> drawable;
    jt::TextureManagerInterface& tm { getTextureManager() };
    void SetUp() override { drawable = GetParam()->createDrawable(tm); }
};

INSTANTIATE_TEST_SUITE_P(DrawableImplTest, DrawableImplTestFixture,
    ::testing::Values(std::make_shared<SpriteFactory>(), std::make_shared<AnimationFactory>(),
        std::make_shared<ShapeFactory>(), std::make_shared<TextFactory>(),
        std::make_shared<BarFactory>(), std::make_shared<TileMapFactory>(),
        std::make_shared<TileMapFactoryWithoutScreenSizeHint>(), std::make_shared<LineFactory>()));

TEST_P(DrawableImplTestFixture, GlobalBoundsEqualLocalBoundsInitially)
{
    ASSERT_EQ(drawable->getLocalBounds(), drawable->getGlobalBounds());
}

TEST_P(DrawableImplTestFixture, InitialOffset)
{
    jt::Vector2f const expected { 0.0f, 0.0f };
    ASSERT_EQ(drawable->getOffset(), expected);
}

TEST_P(DrawableImplTestFixture, OffsetAfterSetOffset)
{
    jt::Vector2f const expected { -55.0f, 12.5f };
    drawable->setOffset(expected);
    ASSERT_EQ(drawable->getOffset(), expected);
}

TEST_P(DrawableImplTestFixture, InitialOrigin)
{
    jt::Vector2f const expected { 0.0f, 0.0f };
    ASSERT_EQ(drawable->getOrigin(), expected);
}

TEST_P(DrawableImplTestFixture, OriginAfterSetOffset)
{
    jt::Vector2f const expected { -55.0f, 12.5f };
    drawable->setOrigin(expected);
    ASSERT_EQ(drawable->getOrigin(), expected);
}

TEST_P(DrawableImplTestFixture, GetIgnoreCamMovementAfterSet)
{
    drawable->setIgnoreCamMovement(false);
    ASSERT_FALSE(drawable->getIgnoreCamMovement());
}

TEST_P(DrawableImplTestFixture, GetPositionInitial)
{
    jt::Vector2f const expected { 0.0f, 0.0f };
    ASSERT_EQ(drawable->getPosition(), expected);
}

TEST_P(DrawableImplTestFixture, GetPositionAfterSetPosition)
{
    jt::Vector2f const expected { 55.5f, -12.0f };
    drawable->setPosition(expected);
    ASSERT_EQ(drawable->getPosition(), expected);
}

TEST_P(DrawableImplTestFixture, GetScaleInitial)
{
    jt::Vector2f const expected { 1.0f, 1.0f };
    ASSERT_EQ(drawable->getScale(), expected);
}

TEST_P(DrawableImplTestFixture, GetScaleAfterSetScale)
{
    jt::Vector2f const expected { 55.5f, -12.0f };
    drawable->setScale(expected);
    ASSERT_EQ(drawable->getScale(), expected);
}

TEST_P(DrawableImplTestFixture, DrawWithoutUpdate) { drawable->draw(getRenderTarget()); }

TEST_P(DrawableImplTestFixture, DrawWithNullptr) { drawable->draw(nullptr); }

TEST_P(DrawableImplTestFixture, Draw)
{
    drawable->update(0.1f);
    drawable->draw(getRenderTarget());
}

TEST_P(DrawableImplTestFixture, DrawWithCamOffset)
{
    jt::DrawableImpl::setCamOffset(jt::Vector2f { -100.0f, -100.0f });
    drawable->update(0.1f);
    drawable->draw(getRenderTarget());
    jt::DrawableImpl::setCamOffset(jt::Vector2f { 0.0f, 0.0f });
}

TEST_P(DrawableImplTestFixture, DrawWithShadow)
{
    drawable->setShadow(jt::colors::Green, jt::Vector2f { 4, 4 });
    drawable->update(0.1f);
    drawable->draw(getRenderTarget());
}

TEST_P(DrawableImplTestFixture, GetColorAfterSetColor)
{
    drawable->setColor(jt::colors::Red);
    ASSERT_EQ(drawable->getColor(), jt::colors::Red);
}

TEST_P(DrawableImplTestFixture, GetColorInitial)
{
    ASSERT_EQ(drawable->getColor(), jt::colors::White);
}

TEST_P(DrawableImplTestFixture, DrawWithSetColor)
{
    drawable->setColor(jt::colors::Red);
    drawable->update(0.1f);
    drawable->draw(getRenderTarget());
}

TEST_P(DrawableImplTestFixture, DrawWithFlash)
{
    drawable->flash(5.0f);
    drawable->update(0.1f);
    auto renderTarget = getRenderTarget();
    drawable->draw(renderTarget);
    drawable->update(5.0f);
    drawable->draw(renderTarget);
}

TEST_P(DrawableImplTestFixture, DrawWithShake)
{
    drawable->shake(5.0f, 0.02f);
    drawable->update(0.1f);
    auto renderTarget = getRenderTarget();
    drawable->draw(renderTarget);
    drawable->update(5.0f);
    drawable->draw(renderTarget);
}

TEST_P(DrawableImplTestFixture, DrawScaled)
{
    drawable->setScale(jt::Vector2f { 2.0f, 2.0f });
    drawable->update(0.1f);
    jt::DrawableImpl::setCamOffset(jt::Vector2f { 100.0f, 100.0f });
    drawable->draw(getRenderTarget());
}

TEST_P(DrawableImplTestFixture, InitialRotations)
{
    ASSERT_FLOAT_EQ(drawable->getRotation(), 0.0f);
}

TEST_P(DrawableImplTestFixture, RotateSetsRotation)
{
    drawable->setRotation(22.5f);
    ASSERT_FLOAT_EQ(drawable->getRotation(), 22.5f);
}

TEST_P(DrawableImplTestFixture, DrawRotated)
{
    drawable->setOrigin(jt::Vector2f { 16.0f, 16.0f });
    drawable->setRotation(22.5f);
    drawable->update(0.1f);
    jt::DrawableImpl::setCamOffset(jt::Vector2f { 100.0f, 100.0f });
    drawable->draw(getRenderTarget());
}

TEST_P(DrawableImplTestFixture, GetFlashColorReturnsWhiteByDefault)
{
    ASSERT_EQ(drawable->getFlashColor(), jt::colors::White);
}

TEST_P(DrawableImplTestFixture, GetFlashColorAfterSet)
{
    drawable->setFlashColor(jt::colors::Yellow);
    ASSERT_EQ(drawable->getFlashColor(), jt::colors::Yellow);
}

TEST_P(DrawableImplTestFixture, UpdateAndDrawWithFlash)
{
    drawable->flash(0.5f, jt::colors::Red);

    ASSERT_EQ(drawable->getFlashColor(), jt::colors::Red);
    drawable->update(0.25f);
    drawable->draw(getRenderTarget());
}

TEST_P(DrawableImplTestFixture, GetShadowActiveIsFalseByDefault)
{
    ASSERT_FALSE(drawable->getShadowActive());
}

TEST_P(DrawableImplTestFixture, GetShadowActiveIsTrueAfterSetShadowActive)
{
    drawable->setShadowActive(true);
    ASSERT_TRUE(drawable->getShadowActive());
}

TEST_P(DrawableImplTestFixture, GetShadowColorReturnsBlackByDefault)
{
    ASSERT_EQ(drawable->getShadowColor(), jt::colors::Black);
}

TEST_P(DrawableImplTestFixture, GetShadowColorAfterSet)
{
    drawable->setShadowColor(jt::colors::Yellow);
    ASSERT_EQ(drawable->getShadowColor(), jt::colors::Yellow);
}
