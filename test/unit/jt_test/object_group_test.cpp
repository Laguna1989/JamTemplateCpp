#include "mocks/mock_game.hpp"
#include "mocks/mock_object.hpp"
#include "object_group.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using Group = jt::ObjectGroup<MockObject>;
using ::testing::_;

class ObjectGroupInitialTest : public ::testing::Test {
protected:
    Group g;
};

TEST_F(ObjectGroupInitialTest, IsEmptyReturnsTrue) { ASSERT_EQ(g.size(), 0); }
TEST_F(ObjectGroupInitialTest, BeginEqualsEnd) { ASSERT_EQ(g.begin(), g.end()); }
TEST_F(ObjectGroupInitialTest, GlobalBeginEqualsBegin) { ASSERT_EQ(jt::begin(g), g.begin()); }
TEST_F(ObjectGroupInitialTest, GlobalEndEqualsEnd) { ASSERT_EQ(jt::end(g), g.end()); }
TEST_F(ObjectGroupInitialTest, CBeginEqualsCEnd) { ASSERT_EQ(g.cbegin(), g.cend()); }
TEST_F(ObjectGroupInitialTest, AgeIsZero) { ASSERT_EQ(g.getAge(), 0.0f); }
TEST_F(ObjectGroupInitialTest, IsAlive) { ASSERT_TRUE(g.isAlive()); }

#ifndef JT_ENABLE_WEB
TEST_F(ObjectGroupInitialTest, GetGameWillThrow) { ASSERT_ANY_THROW(g.getGame()); }
#endif

class ObjectGroupTestWithGame : public ::testing::Test {
public:
    std::shared_ptr<jt::GameInterface> game;
    Group g;
    void SetUp() override
    {
        game = std::make_shared<MockGame>();
        g.setGameInstance(game);
    }
};

TEST_F(ObjectGroupTestWithGame, PushBackObject)
{
    auto mo = std::make_shared<MockObject>();
    g.push_back(mo);

    ASSERT_EQ(g.size(), 1);
}

TEST_F(ObjectGroupTestWithGame, EmplaceBackObject)
{
    auto mo = std::make_shared<MockObject>();
    g.emplace_back(std::move(mo));

    ASSERT_EQ(g.size(), 1);
}

TEST_F(ObjectGroupTestWithGame, atReturnsCorrectPointer)
{
    auto mo = std::make_shared<MockObject>();
    g.push_back(mo);

    ASSERT_EQ(g.at(0).lock(), mo);
}

TEST_F(ObjectGroupTestWithGame, UpdateRemovesObjectWhenWeakPointerExpires)
{
    // shared pointer is created on the fly, weak pointer is created from that shared pointer,
    // shared pointer is destroyed after that.
    g.emplace_back(std::make_shared<MockObject>());
    ASSERT_TRUE(g.at(0).expired());

    // update will sort out the weak pointer, as it is expired.
    g.update(0.0f);
    ASSERT_EQ(g.size(), 0);
}

TEST_F(ObjectGroupTestWithGame, UpdateOfObjectGroupDoesNotUpdateGameObject)
{
    auto mo = std::make_shared<MockObject>();
    g.push_back(mo);

    // update is not called
    EXPECT_CALL(*mo, doUpdate(_)).Times(0);
    g.update(0.5f);
}

TEST_F(ObjectGroupTestWithGame, DrawOfObjectGroupDoesNotDrawGameObject)
{
    auto mo = std::make_shared<MockObject>();
    g.push_back(mo);
    // update is not called!
    EXPECT_CALL(*mo, doDraw()).Times(0);
    g.draw();
}

TEST_F(ObjectGroupTestWithGame, RangedBaseForLoopIsPossibleForObjectGroup)
{
    auto mo1 = std::make_shared<MockObject>();
    auto mo2 = std::make_shared<MockObject>();
    g.push_back(mo1);
    g.push_back(mo2);

    std::size_t count { 0 };

    for (auto const wptr : g) {
        count++;
    }

    ASSERT_EQ(count, 2);
}
