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

class MockInput : public jt::InputManagerInterface {
public:
    MOCK_METHOD(std::shared_ptr<jt::MouseInputInterface>, mouse, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::KeyboardInputInterface>, keyboard, (), (override));
    MOCK_METHOD(void, update, (const jt::MousePosition&), (override));
    MOCK_METHOD(void, reset, (), (override));
};

class MockMouse : public jt::MouseInputInterface {
public:
    MOCK_METHOD(void, updateMousePosition, (const jt::MousePosition&), (override));
    MOCK_METHOD(void, updateButtons, (), (override));
    MOCK_METHOD(jt::Vector2, getMousePositionWorld, (), (override));
    MOCK_METHOD(jt::Vector2, getMousePositionScreen, (), (override));
    MOCK_METHOD(bool, pressed, (jt::MouseButtonCode), (override));
    MOCK_METHOD(bool, justReleased, (jt::MouseButtonCode), (override));
    MOCK_METHOD(bool, justPressed, (jt::MouseButtonCode), (override));
    MOCK_METHOD(bool, released, (jt::MouseButtonCode), (override));
    MOCK_METHOD(void, reset, (), (override));
};

TEST(ButtonTest, IsOverWithMockMouseReturnsTrueWhenOver)
{
    auto game = std::make_shared<testing::NiceMock<MockGame>>();
    auto input = std::make_shared<testing::NiceMock<MockInput>>();
    auto mouse = std::make_shared<testing::NiceMock<MockMouse>>();
    ON_CALL(*game, input()).WillByDefault(testing::Return(input));
    ON_CALL(*input, mouse()).WillByDefault(testing::Return(mouse));
    ON_CALL(*mouse, getMousePositionScreen()).WillByDefault(testing::Return(jt::Vector2 { 5, 5 }));
    jt::Button b {};
    b.setGameInstance(game);

    ASSERT_TRUE(b.IsMouseOver());
}

TEST(ButtonTest, IsOverWithMockMouseReturnsFalseWhenNotOver)
{
    auto game = std::make_shared<testing::NiceMock<MockGame>>();
    auto input = std::make_shared<testing::NiceMock<MockInput>>();
    auto mouse = std::make_shared<testing::NiceMock<MockMouse>>();
    ON_CALL(*game, input()).WillByDefault(testing::Return(input));
    ON_CALL(*input, mouse()).WillByDefault(testing::Return(mouse));
    ON_CALL(*mouse, getMousePositionScreen())
        .WillByDefault(testing::Return(jt::Vector2 { 50, 50 }));
    jt::Button b {};
    b.setGameInstance(game);

    ASSERT_FALSE(b.IsMouseOver());
}

TEST(ButtonTest, UpdateWithInput)
{
    auto game = std::make_shared<testing::NiceMock<MockGame>>();
    auto input = std::make_shared<testing::NiceMock<MockInput>>();
    auto mouse = std::make_shared<testing::NiceMock<MockMouse>>();
    ON_CALL(*game, input()).WillByDefault(testing::Return(input));
    ON_CALL(*input, mouse()).WillByDefault(testing::Return(mouse));
    ON_CALL(*mouse, getMousePositionScreen()).WillByDefault(testing::Return(jt::Vector2 { 5, 5 }));
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

TEST(ButtonTest, DrawInActiveButton)
{
    auto game = std::make_shared<MockGame>();
    EXPECT_CALL(*game, input());
    jt::Button b {};
    b.setActive(false);
    b.setGameInstance(game);
    b.update(0.1f);
    EXPECT_CALL(*game, getRenderTarget()).Times(2);
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

TEST(ButtonTest, IsActiveByDefault)
{
    jt::Button b {};
    ASSERT_TRUE(b.getActive());
}

TEST(ButtonTest, IsNotActiveAfterSetInactive)
{
    jt::Button b {};
    b.setActive(false);

    ASSERT_FALSE(b.getActive());
}

TEST(ButtonTest, AddCallback)
{
    jt::Button b {};
    b.addCallback([]() {});
    ASSERT_EQ(b.getCallbackCount(), 1U);
}

TEST(ButtonTest, CallbacksAreEmptyAfterClearCallbacks)
{
    jt::Button b {};
    b.addCallback([]() {});
    b.clearCallbacks();
    ASSERT_EQ(b.getCallbackCount(), 0U);
}
