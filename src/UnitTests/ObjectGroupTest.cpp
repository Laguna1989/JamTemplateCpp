#include "../JamTemplate/ObjectGroup.hpp"
#include "../JamTemplate/Game.hpp"
#include "MockObject.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using Group = JamTemplate::ObjectGroup<MockObject>;
using JamTemplate::Game;
using ::testing::_;

TEST(ObjectGroupTest, InitialGroupIsEmpty)
{
    Group g {};

    EXPECT_EQ(g.size(), 0);
    EXPECT_ANY_THROW((void)g.at(0));
    EXPECT_EQ(g.begin(), g.end());
    EXPECT_EQ(g.getAge(), 0.0f);
    EXPECT_TRUE(g.isAlive());
    EXPECT_ANY_THROW(g.getGame());
}

class ObjectGroupTestWithGame : public ::testing::Test {
public:
    std::shared_ptr<Game> game;
    Group g;
    void SetUp() override
    {
        game = std::make_shared<Game>(1, 1, 1.0f, "");
        EXPECT_THROW(g.getGame(), std::exception);
        g.setGameInstance(game);
        EXPECT_NO_THROW(g.getGame());
    }
};

TEST_F(ObjectGroupTestWithGame, PushBackObject)
{
    auto mo = std::make_shared<MockObject>();
    g.push_back(mo);

    EXPECT_EQ(g.size(), 1);
    EXPECT_NO_THROW((void)g.at(0));

    EXPECT_EQ(mo.use_count(), 1);
    auto const mo2 = g.at(0).lock();
    EXPECT_EQ(mo.use_count(), 2);
}

TEST_F(ObjectGroupTestWithGame, EmplaceBackObject)
{
    auto mo = std::make_shared<MockObject>();
    // this is more performant than push_back, because the weak_pointer is moved and not copied.
    g.emplace_back(mo);

    EXPECT_EQ(g.size(), 1);
    EXPECT_NO_THROW((void)g.at(0));

    EXPECT_EQ(mo.use_count(), 1);
    auto const mo2 = g.at(0).lock();
    EXPECT_EQ(mo.use_count(), 2);
}

// this is a "negative test", because no owning shared pointer is kept, but only the weak pointer.
TEST_F(ObjectGroupTestWithGame, EmplaceBackObjectWithoutOwningPointer)
{
    // shared pointer is created on the fly, weak pointer is created from that shared pointer,
    // shared pointer is destroyed after that.
    g.emplace_back(std::make_shared<MockObject>());

    EXPECT_EQ(g.size(), 1);
    EXPECT_NO_THROW((void)g.at(0));
    EXPECT_TRUE(g.at(0).expired());
    auto const mo = g.at(0).lock();
    EXPECT_EQ(mo.use_count(), 0);

    // update will sort out the weak pointer, as it is expired.
    g.update(0.0f);
    EXPECT_EQ(g.size(), 0);
}

TEST_F(ObjectGroupTestWithGame, UpdateOfObjectGroupDoesNotUpdateGameObject)
{
    auto mo = std::make_shared<MockObject>();
    // this is more performant than push_back, because the weak_pointer is moved and not copied.
    g.emplace_back(mo);
    ASSERT_EQ(g.size(), 1);

    // update is not called!
    EXPECT_CALL(*mo, doUpdate(_)).Times(0);
    g.update(0.5f);

    EXPECT_EQ(g.size(), 1);
}

TEST_F(ObjectGroupTestWithGame, DrawOfObjectGroupDoesNotDrawGameObject)
{
    auto mo = std::make_shared<MockObject>();
    // this is more performant than push_back, because the weak_pointer is moved and not copied.
    g.emplace_back(mo);
    ASSERT_EQ(g.size(), 1);

    // update is not called!
    EXPECT_CALL(*mo, doDraw()).Times(0);
    g.draw();
}

TEST_F(ObjectGroupTestWithGame, RangedBaseForLoopIsPossibleForObjectGroup)
{
    auto mo1 = std::make_shared<MockObject>();
    auto mo2 = std::make_shared<MockObject>();
    // this is more performant than push_back, because the weak_pointer is moved and not copied.
    g.emplace_back(mo1);
    g.emplace_back(mo2);

    ASSERT_EQ(g.size(), 2);

    std::size_t count { 0 };

    for (auto const wptr : g) {
        count++;
        // do something with wptr
    }

    EXPECT_EQ(count, 2);
}
