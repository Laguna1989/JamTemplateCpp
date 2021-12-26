#include "color.hpp"
#include "drawable_helpers.hpp"
#include "mocks/mock_drawable.hpp"
#include "mocks/mock_tween.hpp"
#include "sdl_setup.hpp"
#include "shape.hpp"
#include "texture_manager_impl.hpp"
#include "tweens/tween_alpha.hpp"
#include "tweens/tween_color.hpp"
#include "tweens/tween_position.hpp"
#include "tweens/tween_rotation.hpp"
#include "tweens/tween_scale.hpp"
#include "vector.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ta = jt::TweenAlpha;
using tc = jt::TweenColor;
using tp = jt::TweenPosition;
using ts = jt::TweenScale;
using tr = jt::TweenRotation;
using tb = jt::Tween;

class TweenBaseTest : public ::testing::Test {
public:
    void SetUp() override
    {
        tm = getTextureManager();
        m_obj = jt::dh::createShapeRect(jt::Vector2f { 20.0f, 20.0f }, jt::colors::White, tm);
    }

protected:
    jt::TextureManagerInterface& tm { getTextureManager() };
    std::shared_ptr<jt::DrawableInterface> m_obj;
};

TEST_F(TweenBaseTest, KillSetsAliveToFalse)
{
    tb t(m_obj, 1.0f);

    t.kill();
    EXPECT_FALSE(t.isAlive());
}

TEST_F(TweenBaseTest, CancelSetsAliveToFalse)
{
    tb t(m_obj, 1.0f);

    t.cancel();
    EXPECT_FALSE(t.isAlive());
}

TEST_F(TweenBaseTest, AliveIsFalseAfterTweenFinishes)
{
    tb t(m_obj, 1.0f);

    t.update(1.1f);

    ASSERT_FALSE(t.isAlive());
}

TEST_F(TweenBaseTest, FinishCallbackIsInvoked)
{
    bool invoked { false };
    tb t(m_obj, 1.0f);
    t.addCompleteCallback([&invoked]() { invoked = true; });
    t.finish();
    ASSERT_TRUE(invoked);
}

TEST_F(TweenBaseTest, GetRepeatReturnsFalseByDefault)
{
    tb t(m_obj, 1.0f);

    ASSERT_FALSE(t.getRepeat());
}

TEST_F(TweenBaseTest, GetRepeatReturnsTrueAfterSetRepeat)
{
    tb t(m_obj, 1.0f);

    t.setRepeat(true);
    ASSERT_TRUE(t.getRepeat());
}

TEST_F(TweenBaseTest, CalledRepeatedly)
{
    int count { 0 };
    tb t(m_obj, 1.0f);
    t.addCompleteCallback([&count]() { count++; });
    t.setRepeat(true);
    t.finish();
    t.finish();
    EXPECT_EQ(count, 2);
    t.finish();
    EXPECT_EQ(count, 3);
}

TEST_F(TweenBaseTest, UpdateChangesAge)
{
    tb t(m_obj, 1.0f);
    float timeIncr = 0.5f;
    t.update(timeIncr);
    EXPECT_EQ(t.getAge(), timeIncr);
}

TEST_F(TweenBaseTest, StartDelay)
{
    tb t(m_obj, 1.0f);
    float const startDelay = 0.5f;
    t.setStartDelay(startDelay);
    EXPECT_EQ(t.getStartDelay(), startDelay);
    t.update(startDelay);
    EXPECT_EQ(t.getAge(), 0.0f);
}

TEST_F(TweenBaseTest, SkipFrames)
{
    tb t(m_obj, 1.0f);
    int const skipFrames = 2;

    t.setSkipFrames(skipFrames);
    EXPECT_EQ(t.getSkipFrames(), skipFrames);

    // expect first two calls to update to do nothing (regardless of update time)
    t.update(100.0f);
    EXPECT_EQ(t.getAge(), 0.0f);
    t.update(1.0f);
    EXPECT_EQ(t.getAge(), 0.0f);
    t.update(1.0f);
    EXPECT_EQ(t.getAge(), 1.0f);
}

TEST_F(TweenBaseTest, AgePercentConversion)
{
    MockTween t(m_obj, 1.0f);

    t.setAgePercentConversion([](float age) { return age / 2.0f; });
    EXPECT_CALL(t, doUpdateObject(::testing::_, 1.0f / 2.0f));
    t.update(1.0f);

    t.setAgePercentConversion([](float /*unused*/) { return 1.2f; });
    EXPECT_CALL(t, doUpdateObject(::testing::_, 1.2f)).Times(3);
    t.update(0.0f);
    t.update(9.0f);
    t.update(100.0f);
}

TEST_F(TweenBaseTest, TweenCanHandleDestroyedObject)
{
    auto obj = std::make_shared<MockDrawable>();
    tb t(obj, 1.0f);

    EXPECT_NO_THROW(t.update(0.25f));

    // deliberately destroy object
    obj = nullptr;
    EXPECT_NO_THROW(t.update(0.25f));
}

TEST_F(TweenBaseTest, Alpha)
{
    float const time { 5.0f };

    EXPECT_EQ(m_obj->getColor().a, 255U);

    uint8_t const start { 0U };
    uint8_t const end { 255U };

    auto const twa = ta::create(m_obj, time, start, end);
    twa->update(0.0f);
    EXPECT_EQ(m_obj->getColor().a, start);
    twa->update(time);
    EXPECT_EQ(m_obj->getColor().a, end);
}

TEST_F(TweenBaseTest, Color)
{
    float const time { 5.0f };

    jt::Color const start { 255, 255, 255, 255 };
    jt::Color const end { 0, 0, 0, 255 };

    auto const twc = tc::create(m_obj, time, start, end);
    twc->update(0.0f);
    EXPECT_EQ(m_obj->getColor(), start);
    twc->update(time);
    EXPECT_EQ(m_obj->getColor(), end);
}

TEST_F(TweenBaseTest, Position)
{
    float const time { 5.0f };

    jt::Vector2f const start { 10.0f, 10.0f };
    jt::Vector2f const end { -15.0f, -15.0f };

    auto const twp = tp::create(m_obj, time, start, end);
    twp->update(0.0f);
    EXPECT_EQ(m_obj->getPosition(), start);
    twp->update(time);
    EXPECT_EQ(m_obj->getPosition(), end);
}

TEST_F(TweenBaseTest, Scale)
{
    float const time { 5.0f };

    jt::Vector2f const start { -1.0f, -1.0f };
    jt::Vector2f const end { 5.0f, 5.0f };

    auto const tws = ts::create(m_obj, time, start, end);
    tws->update(0.0f);
    EXPECT_EQ(m_obj->getScale(), start);
    tws->update(time);
    EXPECT_EQ(m_obj->getScale(), end);
}

TEST_F(TweenBaseTest, Rotation)
{
    float const time { 5.0f };

    float const start { 0.0f };
    float const end { 180.0f };

    auto const trs = tr::create(m_obj, time, start, end);
    trs->update(0.0f);
    EXPECT_EQ(m_obj->getRotation(), start);
    trs->update(time);
    EXPECT_EQ(m_obj->getRotation(), end);
}
