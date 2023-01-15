﻿#include "drawables_impl_test.hpp"
#include <backend_setup.hpp>
#include <texture_manager_impl.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

class DrawableImplTestFixture
    : public ::testing::TestWithParam<std::shared_ptr<DrawableFactoryInterface>> {
protected:
    std::shared_ptr<jt::DrawableInterface> drawable;
    jt::TextureManagerInterface& tm { getTextureManager() };
    void SetUp() override { drawable = GetParam()->createDrawable(tm); }
    void TearDown() override
    {
        // reset static cam offset just to make sure
        jt::DrawableImpl::setCamOffset(jt::Vector2f { 0.0f, 0.0f });
    }
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

TEST_P(DrawableImplTestFixture, GetScreenPositionInitial)
{
    jt::Vector2f const expected { 0.0f, 0.0f };
    ASSERT_EQ(drawable->getScreenPosition(), expected);
}

TEST_P(DrawableImplTestFixture, GetPositionAfterSetPosition)
{
    jt::Vector2f const expected { 55.5f, -12.0f };
    drawable->setPosition(expected);
    ASSERT_EQ(drawable->getPosition(), expected);
}

TEST_P(DrawableImplTestFixture, GetScreenPositionAfterSetPosition)
{
    jt::Vector2f const expected { 55.5f, -12.0f };
    drawable->setPosition(expected);
    ASSERT_EQ(drawable->getScreenPosition(), expected);
}

TEST_P(DrawableImplTestFixture, GetInitialScreenPositionAfterCamMove)
{
    jt::Vector2f const expected { 55.5f, -12.0f };
    jt::DrawableImpl::setCamOffset(expected);
    ASSERT_EQ(drawable->getScreenPosition(), expected);
}

TEST_P(DrawableImplTestFixture, GetPositionAfterCamMove)
{
    jt::Vector2f const expected { 100.0f, 200.0f };
    drawable->setPosition(expected);
    jt::DrawableImpl::setCamOffset(jt::Vector2f { 100.0f, 200.0f });
    ASSERT_EQ(drawable->getScreenPosition(), 2.0f * expected);
}

TEST_P(DrawableImplTestFixture, GetInitialScreenPositionWithCamFactorSmallerOne)
{
    jt::Vector2f const expected { 100.0f, 200.0f };
    drawable->setPosition(expected);
    drawable->setCamMovementFactor(0.5f);
    ASSERT_EQ(drawable->getScreenPosition(), expected);
}

TEST_P(DrawableImplTestFixture, GetInitialScreenPositionWithCamFactorBiggerOne)
{
    jt::Vector2f const expected { 100.0f, 200.0f };
    drawable->setPosition(expected);
    drawable->setCamMovementFactor(1.5f);
    ASSERT_EQ(drawable->getScreenPosition(), expected);
}

TEST_P(DrawableImplTestFixture, GetScreenPositionWithCamFactorSmallerOne1)
{
    jt::Vector2f const worldPosition { 100.0f, 200.0f };
    drawable->setPosition(worldPosition);
    float const camMovementFactor { 0.1f };
    drawable->setCamMovementFactor(camMovementFactor);
    auto camOffset = jt::Vector2f { 100.0f, 200.0f };
    jt::DrawableImpl::setCamOffset(camOffset);
    ASSERT_EQ(drawable->getScreenPosition(), worldPosition + camMovementFactor * camOffset);
}

TEST_P(DrawableImplTestFixture, GetScreenPositionWithCamFactorSmallerOne2)
{
    jt::Vector2f const worldPosition { 1.0f, 200.0f };
    drawable->setPosition(worldPosition);
    float const camMovementFactor { 0.1f };
    drawable->setCamMovementFactor(camMovementFactor);
    auto camOffset = jt::Vector2f { 1.0f, 0.0f };
    jt::DrawableImpl::setCamOffset(camOffset);
    ASSERT_EQ(drawable->getScreenPosition(), worldPosition + camMovementFactor * camOffset);
}

TEST_P(DrawableImplTestFixture, GetScreenPositionWithCamFactorBiggerOne)
{
    jt::Vector2f const worldPosition { 100.0f, 200.0f };
    drawable->setPosition(worldPosition);
    float const camMovementFactor { 2.0f };
    drawable->setCamMovementFactor(camMovementFactor);
    auto camOffset = jt::Vector2f { 100.0f, 200.0f };
    jt::DrawableImpl::setCamOffset(camOffset);
    ASSERT_EQ(drawable->getScreenPosition(), worldPosition + camMovementFactor * camOffset);
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

TEST_P(DrawableImplTestFixture, DrawWithoutUpdate) { drawable->draw(getRenderTargetContainer()); }

TEST_P(DrawableImplTestFixture, DrawWithNullptr) { drawable->draw(nullptr); }

TEST_P(DrawableImplTestFixture, Draw)
{
    drawable->update(0.1f);
    drawable->draw(getRenderTargetContainer());
}

TEST_P(DrawableImplTestFixture, DrawWithCamOffset)
{
    jt::DrawableImpl::setCamOffset(jt::Vector2f { -100.0f, -100.0f });
    drawable->update(0.1f);
    drawable->draw(getRenderTargetContainer());
    jt::DrawableImpl::setCamOffset(jt::Vector2f { 0.0f, 0.0f });
}

TEST_P(DrawableImplTestFixture, DrawWithShadow)
{
    drawable->setShadow(jt::colors::Green, jt::Vector2f { 4, 4 });
    drawable->update(0.1f);
    drawable->draw(getRenderTargetContainer());
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
    drawable->draw(getRenderTargetContainer());
}

TEST_P(DrawableImplTestFixture, DrawWithFlash)
{
    drawable->flash(5.0f);
    drawable->update(0.1f);
    auto renderTarget = getRenderTargetContainer();
    drawable->draw(renderTarget);
    drawable->update(5.0f);
    drawable->draw(renderTarget);
}

TEST_P(DrawableImplTestFixture, DrawWithFlicker)
{
    drawable->flicker(1.0f, 0.11f);
    drawable->update(0.1f);
    auto renderTarget = getRenderTargetContainer();
    drawable->draw(renderTarget);
    drawable->update(1.0f);
    drawable->draw(renderTarget);
}

TEST_P(DrawableImplTestFixture, DrawWithShake)
{
    drawable->shake(5.0f, 0.02f);
    drawable->update(0.1f);
    auto renderTarget = getRenderTargetContainer();
    drawable->draw(renderTarget);
    drawable->update(5.0f);
    drawable->draw(renderTarget);
}

TEST_P(DrawableImplTestFixture, DrawScaled)
{
    drawable->setScale(jt::Vector2f { 2.0f, 2.0f });
    drawable->update(0.1f);
    jt::DrawableImpl::setCamOffset(jt::Vector2f { 100.0f, 100.0f });
    drawable->draw(getRenderTargetContainer());
    jt::DrawableImpl::setCamOffset(jt::Vector2f { 0.0f, 0.0f });
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
    drawable->draw(getRenderTargetContainer());
    jt::DrawableImpl::setCamOffset(jt::Vector2f { 0.0f, 0.0f });
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
    drawable->draw(getRenderTargetContainer());
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
    drawable->setShadow(jt::colors::Yellow, jt::Vector2f { 1.0f, 1.0f });
    ASSERT_EQ(drawable->getShadowColor(), jt::colors::Yellow);
}

TEST_P(DrawableImplTestFixture, GetSetBlendModeMul)
{
    auto const expectedBlendMode = jt::BlendMode::MUL;
    drawable->setBlendMode(expectedBlendMode);
    ASSERT_EQ(drawable->getBlendMode(), expectedBlendMode);
}

TEST_P(DrawableImplTestFixture, GetSetBlendModeAdd)
{
    auto const expectedBlendMode = jt::BlendMode::ADD;
    drawable->setBlendMode(expectedBlendMode);
    ASSERT_EQ(drawable->getBlendMode(), expectedBlendMode);
}

TEST_P(DrawableImplTestFixture, GetSetBlendModeAlpha)
{
    auto const expectedBlendMode = jt::BlendMode::ALPHA;
    drawable->setBlendMode(expectedBlendMode);
    ASSERT_EQ(drawable->getBlendMode(), expectedBlendMode);
}

TEST_P(DrawableImplTestFixture, DrawWithBlendModeMul)
{
    auto const expectedBlendMode = jt::BlendMode::MUL;
    drawable->setBlendMode(expectedBlendMode);
    drawable->update(0.0f);
    drawable->draw(getRenderTargetContainer());
}

TEST_P(DrawableImplTestFixture, DrawWithBlendModeAdd)
{
    auto const expectedBlendMode = jt::BlendMode::ADD;
    drawable->setBlendMode(expectedBlendMode);
    drawable->update(0.0f);
    drawable->draw(getRenderTargetContainer());
}

TEST_P(DrawableImplTestFixture, DrawWithBlendModeAlpha)
{
    auto const expectedBlendMode = jt::BlendMode::ALPHA;
    drawable->setBlendMode(expectedBlendMode);
    drawable->update(0.0f);
    drawable->draw(getRenderTargetContainer());
}

TEST_P(DrawableImplTestFixture, InitialOffsetModeIsManual)
{
    ASSERT_EQ(drawable->getOffsetMode(), jt::OffsetMode::MANUAL);
}

TEST_P(DrawableImplTestFixture, SetOffsetModeChangesOffsetMode)
{
    drawable->setOffset(jt::OffsetMode::TOPLEFT);
    ASSERT_EQ(drawable->getOffsetMode(), jt::OffsetMode::TOPLEFT);
}

TEST_P(DrawableImplTestFixture, OffsetModesOverridesManualOffsetTopLeft)
{
    auto const offset = jt::Vector2f { -14.0f, 2.2f };
    drawable->setOffset(offset);
    ASSERT_EQ(drawable->getOffset(), offset);
    drawable->setOffset(jt::OffsetMode::TOPLEFT);
    auto const expectedOffset = jt::Vector2f { 0.0f, 0.0f };
    ASSERT_EQ(drawable->getOffset(), expectedOffset);
}

TEST_P(DrawableImplTestFixture, OffsetModesOverridesManualOffsetCenter)
{
    auto const offset = jt::Vector2f { -14.0f, 2.2f };
    drawable->setOffset(offset);
    ASSERT_EQ(drawable->getOffset(), offset);
    drawable->setOffset(jt::OffsetMode::CENTER);
    auto const expectedOffset = -0.5f
        * jt::Vector2f { drawable->getLocalBounds().width, drawable->getLocalBounds().height };
    ASSERT_EQ(drawable->getOffset(), expectedOffset);
}

TEST_P(DrawableImplTestFixture, SetOffsetChangesOffsetModeToManual)
{
    drawable->setOffset(jt::OffsetMode::TOPLEFT);
    ASSERT_EQ(drawable->getOffsetMode(), jt::OffsetMode::TOPLEFT);
    drawable->setOffset(jt::Vector2f { -14.0f, 2.2f });
    ASSERT_EQ(drawable->getOffsetMode(), jt::OffsetMode::MANUAL);
}

TEST_P(DrawableImplTestFixture, isVisibleByDefault) { ASSERT_TRUE(drawable->isVisible()); }

TEST_P(DrawableImplTestFixture, isVisibleWithScreenSizeHint)
{
    drawable->setScreenSizeHint(jt::Vector2f { 100.0f, 100.0f });
    ASSERT_TRUE(drawable->isVisible());
}

TEST_P(DrawableImplTestFixture, isNotVisibleLeft)
{
    if (GetParam()->skipVisibilityCheck()) {
        return;
    }
    drawable->setScreenSizeHint(jt::Vector2f { 100.0f, 100.0f });

    drawable->setPosition(jt::Vector2f { -drawable->getLocalBounds().width - 5.0f, 0.0f });
    ASSERT_FALSE(drawable->isVisible());
}

TEST_P(DrawableImplTestFixture, isNotVisibleRight)
{
    if (GetParam()->skipVisibilityCheck()) {
        return;
    }
    drawable->setScreenSizeHint(jt::Vector2f { 100.0f, 100.0f });

    drawable->setPosition(jt::Vector2f { drawable->getLocalBounds().width + 5.0f + 100.0f, 0.0f });
    ASSERT_FALSE(drawable->isVisible());
}

TEST_P(DrawableImplTestFixture, isNotVisibleBottom)
{
    if (GetParam()->skipVisibilityCheck()) {
        return;
    }
    drawable->setScreenSizeHint(jt::Vector2f { 100.0f, 100.0f });

    drawable->setPosition(jt::Vector2f { 0.0f, drawable->getLocalBounds().height + 5.0f + 100.0f });
    ASSERT_FALSE(drawable->isVisible());
}

TEST_P(DrawableImplTestFixture, isNotVisibleTop)
{
    if (GetParam()->skipVisibilityCheck()) {
        return;
    }
    drawable->setScreenSizeHint(jt::Vector2f { 100.0f, 100.0f });

    drawable->setPosition(jt::Vector2f { 0.0f, -drawable->getLocalBounds().height - 5.0f });
    ASSERT_FALSE(drawable->isVisible());
}

TEST_P(DrawableImplTestFixture, InitialOriginModeIsManual)
{
    ASSERT_EQ(drawable->getOriginMode(), jt::OriginMode::MANUAL);
}

TEST_P(DrawableImplTestFixture, SetOriginModeChangesOriginMode)
{
    drawable->setOrigin(jt::OriginMode::TOPLEFT);
    ASSERT_EQ(drawable->getOriginMode(), jt::OriginMode::TOPLEFT);
}

TEST_P(DrawableImplTestFixture, OriginModesOverridesManualOriginTopLeft)
{
    auto const origin = jt::Vector2f { -14.0f, 2.2f };
    drawable->setOrigin(origin);
    ASSERT_EQ(drawable->getOrigin(), origin);
    drawable->setOrigin(jt::OriginMode::TOPLEFT);
    auto const expectedOrigin = jt::Vector2f { 0.0f, 0.0f };
    ASSERT_EQ(drawable->getOrigin(), expectedOrigin);
}

TEST_P(DrawableImplTestFixture, OriginModesOverridesManualOriginCenter)
{
    auto const origin = jt::Vector2f { -14.0f, 2.2f };
    drawable->setOrigin(origin);
    ASSERT_EQ(drawable->getOrigin(), origin);
    drawable->setOrigin(jt::OriginMode::CENTER);
    auto const expectedOrigin = 0.5f
        * jt::Vector2f { drawable->getLocalBounds().width, drawable->getLocalBounds().height };
    ASSERT_EQ(drawable->getOrigin(), expectedOrigin);
}

TEST_P(DrawableImplTestFixture, SetOriginChangesOriginModeToManual)
{
    drawable->setOrigin(jt::OriginMode::TOPLEFT);
    ASSERT_EQ(drawable->getOriginMode(), jt::OriginMode::TOPLEFT);
    drawable->setOrigin(jt::Vector2f { -14.0f, 2.2f });
    ASSERT_EQ(drawable->getOriginMode(), jt::OriginMode::MANUAL);
}
