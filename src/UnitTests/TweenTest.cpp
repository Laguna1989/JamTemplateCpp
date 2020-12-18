#include "TweenAlpha.hpp"
#include "TweenColor.hpp"
#include "TweenPosition.hpp"
#include "TweenScale.hpp"
#include "Vector.hpp"
#include "Color.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <limits>
#include <utility>

class Object {
public:
    jt::Color getColor() const { return m_col; };
    void setColor(jt::Color const& c) { m_col = c; };

    std::uint8_t getAlpha() { return m_col.a(); };

    jt::Vector2 getPosition() const { return m_pos; };
    void setPosition(jt::Vector2 const& p) { m_pos = p; };

    jt::Vector2 getScale() const { return m_scale; };
    void setScale(jt::Vector2 const& p) { m_scale = p; };

private:
    jt::Color m_col { jt::colors::Black };
    jt::Vector2 m_pos { 0.0f, 0.0f };
    jt::Vector2 m_scale { 1.0f, 1.0f };
};

using ta = jt::TweenAlpha<Object>;
using tc = jt::TweenColor<Object>;
using tp = jt::TweenPosition<Object>;
using ts = jt::TweenScale<Object>;
using tb = jt::Tween<Object>;

class TweenBaseTest : public ::testing::Test {
public:
    void SetUp() override { m_obj = std::make_shared<Object>(); }

protected:
    std::shared_ptr<Object> m_obj;
};

TEST_F(TweenBaseTest, KillSetsAliveToFalse)
{
    tb t(
        m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; }, 1.0f);

    t.kill();
    EXPECT_FALSE(t.isAlive());
}

TEST_F(TweenBaseTest, CancelSetsAliveToFalse)
{
    tb t(
        m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; }, 1.0f);

    t.cancel();
    EXPECT_FALSE(t.isAlive());
}

TEST_F(TweenBaseTest, FinishCallbackIsInvoked)
{
    bool invoked { false };
    tb t(
        m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; }, 1.0f);
    t.addCompleteCallback([&invoked]() { invoked = true; });
    t.finish();
    EXPECT_TRUE(invoked);
}

TEST_F(TweenBaseTest, CalledRepeatedly)
{
    int count { 0 };
    tb t(
        m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; }, 1.0f);
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
    tb t(
        m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; }, 1.0f);
    float timeIncr = 0.5f;
    t.update(timeIncr);
    EXPECT_EQ(t.getAge(), timeIncr);
}

TEST_F(TweenBaseTest, StartDelay)
{
    tb t(
        m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; }, 1.0f);
    float const startDelay = 0.5f;
    t.setStartDelay(startDelay);
    EXPECT_EQ(t.getStartDelay(), startDelay);
    t.update(startDelay);
    EXPECT_EQ(t.getAge(), 0.0f);
}

TEST_F(TweenBaseTest, SkipFrames)
{
    tb t(
        m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; }, 1.0f);
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
    float returnedAgePrecent { 0.0f };
    tb t(
        m_obj,
        [&returnedAgePrecent](auto /*obj*/, auto agepercent) {
            returnedAgePrecent = agepercent;
            return true;
        },
        1.0f);

    t.setAgePercentConversion([](float age) { return age / 2.0f; });
    t.update(1.0f);
    EXPECT_EQ(returnedAgePrecent, 1.0f / 2.0f);

    t.setAgePercentConversion([](float /*unused*/) { return 1.2f; });
    t.update(0.0f);
    EXPECT_EQ(returnedAgePrecent, 1.2f);
    t.update(9.0f);
    EXPECT_EQ(returnedAgePrecent, 1.2f);
    t.update(100.0f);
    EXPECT_EQ(returnedAgePrecent, 1.2f);
}

TEST_F(TweenBaseTest, TweenCanHandleDestroyedObject)
{
    auto obj = std::make_shared<Object>();
    float returnedAgePrecent { 0.0f };
    tb t(
        obj,
        [&returnedAgePrecent](auto /*obj*/, auto agepercent) {
            returnedAgePrecent = agepercent;
            return true;
        },
        1.0f);

    EXPECT_NO_THROW(t.update(0.25f));

    // deliberately destroy object
    obj = nullptr;
    EXPECT_NO_THROW(t.update(0.25f));
}

TEST_F(TweenBaseTest, Alpha)
{
    float const time { 5.0f };

    EXPECT_EQ(m_obj->getAlpha(), 255U);

    uint8_t const start { 0U };
    uint8_t const end { 255U };

    auto const twa = ta::create(m_obj, time, start, end);
    twa->update(0.0f);
    EXPECT_EQ(m_obj->getAlpha(), start);
    twa->update(time);
    EXPECT_EQ(m_obj->getAlpha(), end);
}

TEST_F(TweenBaseTest, Color)
{
    float const time { 5.0f };

    ASSERT_EQ(m_obj->getColor(), jt::colors::Black);

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

    jt::Vector2 const start { 10.0f, 10.0f };
    jt::Vector2 const end { -15.0f, -15.0f };

    auto const twp = tp::create(m_obj, time, start, end);
    twp->update(0.0f);
    EXPECT_EQ(m_obj->getPosition(), start);
    twp->update(time);
    EXPECT_EQ(m_obj->getPosition(), end);
}

TEST_F(TweenBaseTest, Scale)
{
    float const time { 5.0f };

    jt::Vector2 const start { -1.0f, -1.0f };
    jt::Vector2 const end { 5.0f, 5.0f };

    auto const tws = ts::create(m_obj, time, start, end);
    tws->update(0.0f);
    EXPECT_EQ(m_obj->getScale(), start);
    tws->update(time);
    EXPECT_EQ(m_obj->getScale(), end);
}
