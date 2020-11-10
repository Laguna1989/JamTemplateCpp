#include "TweenAlpha.hpp"
#include "TweenColor.hpp"
#include "TweenPosition.hpp"
#include "TweenScale.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <limits>
#include <utility>

class Object {
public:
    sf::Color getColor() const { return m_col; };
    void setColor(sf::Color const& c) { m_col = c; };

    std::uint8_t getAlpha() { return m_col.a; };

    sf::Vector2f getPosition() const { return m_pos; };
    void setPosition(sf::Vector2f const& p) { m_pos = p; };

    sf::Vector2f getScale() const { return m_scale; };
    void setScale(sf::Vector2f const& p) { m_scale = p; };

private:
    sf::Color m_col { sf::Color::Black };
    sf::Vector2f m_pos { 0.0f, 0.0f };
    sf::Vector2f m_scale { 1.0f, 1.0f };
};

using ta = JamTemplate::TweenAlpha<Object>;
using tc = JamTemplate::TweenColor<Object>;
using tp = JamTemplate::TweenPosition<Object>;
using ts = JamTemplate::TweenScale<Object>;
using tb = JamTemplate::Tween<Object>;

class TweenBaseTest : public ::testing::Test {
public:
    void SetUp() override { m_obj = std::make_shared<Object>(); }

protected:
    std::shared_ptr<Object> m_obj;
};

TEST_F(TweenBaseTest, KillSetsAliveToFalse)
{
    tb t(m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; });

    t.kill();
    EXPECT_FALSE(t.isAlive());
}

TEST_F(TweenBaseTest, CancelSetsAliveToFalse)
{
    tb t(m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; });

    t.cancel();
    EXPECT_FALSE(t.isAlive());
}

TEST_F(TweenBaseTest, FinishCallbackIsInvoked)
{
    bool invoked { false };
    tb t(m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; });
    t.addCompleteCallback([&invoked]() { invoked = true; });
    t.finish();
    EXPECT_TRUE(invoked);
}

TEST_F(TweenBaseTest, CalledRepeatedly)
{
    int count { 0 };
    tb t(m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; });
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
    tb t(m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; });
    float timeIncr = 0.5f;
    t.update(timeIncr);
    EXPECT_EQ(t.getAge(), timeIncr);
}

TEST_F(TweenBaseTest, StartDelay)
{
    tb t(m_obj, [](auto /*obj*/, auto /*agepercent*/) { return true; });
    float startDelay = 0.5f;
    t.setStartDelay(startDelay);
    EXPECT_EQ(t.getStartDelay(), startDelay);
    t.update(startDelay);
    EXPECT_EQ(t.getAge(), 0.0f);
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

    ASSERT_EQ(m_obj->getColor(), sf::Color::Black);

    sf::Color const start { 255, 255, 255, 255 };
    sf::Color const end { 0, 0, 0, 255 };

    auto const twc = tc::create(m_obj, time, start, end);
    twc->update(0.0f);
    EXPECT_EQ(m_obj->getColor(), start);
    twc->update(time);
    EXPECT_EQ(m_obj->getColor(), end);
}

TEST_F(TweenBaseTest, Position)
{
    float const time { 5.0f };

    sf::Vector2f const start { 10.0f, 10.0f };
    sf::Vector2f const end { -15.0f, -15.0f };

    auto const twp = tp::create(m_obj, time, start, end);
    twp->update(0.0f);
    EXPECT_EQ(m_obj->getPosition(), start);
    twp->update(time);
    EXPECT_EQ(m_obj->getPosition(), end);
}

TEST_F(TweenBaseTest, Scale)
{
    float const time { 5.0f };

    sf::Vector2f const start { -1.0f, -1.0f };
    sf::Vector2f const end { 5.0f, 5.0f };

    auto const tws = ts::create(m_obj, time, start, end);
    tws->update(0.0f);
    EXPECT_EQ(m_obj->getScale(), start);
    tws->update(time);
    EXPECT_EQ(m_obj->getScale(), end);
}
