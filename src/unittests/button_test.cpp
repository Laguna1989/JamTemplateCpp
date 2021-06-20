#include "button.hpp"
#include "mock_drawable.hpp"
#include "mock_game.hpp"
#include <gtest/gtest.h>

TEST(ButtonTest, InitialValues)
{
    jt::Button b { jt::Vector2u { 32, 16 } };
    jt::Vector2 expectedPos { 0.0f, 0.0f };

    EXPECT_EQ(b.getPosition(), expectedPos);
    EXPECT_EQ(b.getCallbackCount(), 0);
    EXPECT_TRUE(b.getVisible());
}

TEST(ButtonTest, SetVisibleSetsCorrectValue)
{
    jt::Button b { jt::Vector2u { 32, 16 } };
    ASSERT_TRUE(b.getVisible());
    b.setVisible(true);
    EXPECT_TRUE(b.getVisible());
    b.setVisible(false);
    EXPECT_FALSE(b.getVisible());
}

TEST(ButtonTest, UpdateWithoutGameInstanceRaisesException)
{
    jt::Button b {};
    EXPECT_ANY_THROW(b.update(0.1f));
}

TEST(ButtonTest, UpdateWithGameInstanceDoesNotThrow)
{
    auto game = std::make_shared<MockGame>();
    EXPECT_CALL(*game, input());
    jt::Button b {};
    b.setGameInstance(game);
    b.update(0.1f);
    SUCCEED();
}

TEST(ButtonTest, Draw)
{
    auto game = std::make_shared<MockGame>();
    EXPECT_CALL(*game, input());
    jt::Button b {};
    b.setGameInstance(game);
    b.update(0.1f);
    EXPECT_CALL(*game, getRenderTarget());
    b.draw();
    SUCCEED();
}

TEST(ButtonTest, DrawInvisibleButton)
{
    auto game = std::make_shared<MockGame>();
    EXPECT_CALL(*game, input());
    jt::Button b {};
    b.setVisible(false);
    b.setGameInstance(game);
    b.update(0.1f);
    EXPECT_CALL(*game, getRenderTarget()).Times(0);
    b.draw();
    SUCCEED();
}

TEST(ButtonTest, CustomDrawable)
{
    auto game = std::make_shared<MockGame>();
    EXPECT_CALL(*game, input()).Times(2);
    jt::Button b {};
    b.setGameInstance(game);
    b.update(0.1f);

    auto d = std::make_shared<MockDrawable>();
    b.setDrawable(d);
    std::shared_ptr<jt::renderTarget> rt = nullptr;
    EXPECT_CALL(*game, getRenderTarget()).Times(2);
    EXPECT_CALL(*d, update(0.1f));
    b.update(0.1f);
    EXPECT_CALL(*d, draw(rt));
    b.draw();
    SUCCEED();
}
