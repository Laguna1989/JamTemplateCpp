#include "button.hpp"
#include "mocks/mock_drawable.hpp"
#include "mocks/mock_game.hpp"
#include "mocks/mock_input.hpp"
#include "sdl_setup.hpp"
#include "texture_manager_impl.hpp"
#include <gtest/gtest.h>

class ButtonTest : public ::testing::Test {
public:
    jt::TextureManagerInterface& tm { getTextureManager() };

    std::shared_ptr<jt::Button> b { nullptr };
    void SetUp() override
    {
        tm = getTextureManager();
        b = std::make_shared<jt::Button>(jt::Vector2u { 32, 16 }, tm);
    }
};

TEST_F(ButtonTest, InitialPosition)
{
    jt::Vector2f expectedPos { 0.0f, 0.0f };
    ASSERT_EQ(b->getPosition(), expectedPos);
}

TEST_F(ButtonTest, InitialCallbacks) { ASSERT_EQ(b->getCallbackCount(), 0); }

TEST_F(ButtonTest, InitialVisible) { ASSERT_TRUE(b->getVisible()); }

TEST_F(ButtonTest, InitialActive) { ASSERT_TRUE(b->getActive()); }

TEST_F(ButtonTest, GetPositionAfterSetPosition)
{
    jt::Vector2f expectedPos { 20.0f, 20.0f };
    b->setPosition(expectedPos);
    ASSERT_EQ(b->getPosition(), expectedPos);
}

TEST_F(ButtonTest, SetVisibleSetsFalseCorrectValue)
{
    b->setVisible(false);
    ASSERT_FALSE(b->getVisible());
}

TEST_F(ButtonTest, SetVisibleSetsTrueCorrectValue)
{
    b->setVisible(true);
    ASSERT_TRUE(b->getVisible());
}

TEST_F(ButtonTest, UpdateWithoutGameInstanceRaisesException) { ASSERT_ANY_THROW(b->update(0.1f)); }

TEST_F(ButtonTest, UpdateWithGameInstanceDoesNotThrow)
{
    auto game = std::make_shared<MockGame>();
    ::testing::NiceMock<MockInput> input;
    EXPECT_CALL(*game, input()).WillRepeatedly(::testing::ReturnRef(input));
    b->setGameInstance(game);
    b->update(0.1f);
}

TEST_F(ButtonTest, IsOverWithMockMouseReturnsTrueWhenOver)
{
    auto game = std::make_shared<testing::NiceMock<MockGame>>();
    testing::NiceMock<MockInput> input;
    auto mouse = std::make_shared<testing::NiceMock<MockMouseInput>>();
    ON_CALL(*game, input()).WillByDefault(testing::ReturnRef(input));
    ON_CALL(input, mouse()).WillByDefault(testing::Return(mouse));
    ON_CALL(*mouse, getMousePositionScreen()).WillByDefault(testing::Return(jt::Vector2f { 5, 5 }));
    b->setGameInstance(game);

    ASSERT_TRUE(b->isMouseOver());
}

TEST_F(ButtonTest, IsOverWithMockMouseReturnsFalseWhenNotOver)
{
    auto game = std::make_shared<testing::NiceMock<MockGame>>();
    testing::NiceMock<MockInput> input;
    auto mouse = std::make_shared<testing::NiceMock<MockMouseInput>>();
    ON_CALL(*game, input()).WillByDefault(testing::ReturnRef(input));
    ON_CALL(input, mouse()).WillByDefault(testing::Return(mouse));
    ON_CALL(*mouse, getMousePositionScreen())
        .WillByDefault(testing::Return(jt::Vector2f { 50, 50 }));
    b->setGameInstance(game);

    ASSERT_FALSE(b->isMouseOver());
}

TEST_F(ButtonTest, IsOverReturnsFalseWhenNotActive)
{
    auto game = std::make_shared<testing::NiceMock<MockGame>>();
    testing::NiceMock<MockInput> input;
    auto mouse = std::make_shared<testing::NiceMock<MockMouseInput>>();
    ON_CALL(*game, input()).WillByDefault(testing::ReturnRef(input));
    ON_CALL(input, mouse()).WillByDefault(testing::Return(mouse));
    ON_CALL(*mouse, getMousePositionScreen()).WillByDefault(testing::Return(jt::Vector2f { 5, 5 }));
    b->setActive(false);
    b->setGameInstance(game);

    ASSERT_FALSE(b->isMouseOver());
}

TEST_F(ButtonTest, UpdateWithInput)
{
    auto game = std::make_shared<testing::NiceMock<MockGame>>();
    testing::NiceMock<MockInput> input;
    auto mouse = std::make_shared<testing::NiceMock<MockMouseInput>>();
    ON_CALL(*game, input()).WillByDefault(testing::ReturnRef(input));
    ON_CALL(input, mouse()).WillByDefault(testing::Return(mouse));
    ON_CALL(*mouse, getMousePositionScreen()).WillByDefault(testing::Return(jt::Vector2f { 5, 5 }));
    b->setGameInstance(game);

    b->update(0.1f);
    SUCCEED();
}

TEST_F(ButtonTest, Draw)
{
    auto game = std::make_shared<MockGame>();
    ::testing::NiceMock<MockInput> input;
    EXPECT_CALL(*game, input()).WillRepeatedly(::testing::ReturnRef(input));
    b->setGameInstance(game);
    b->update(0.1f);
    b->draw();
    SUCCEED();
}

TEST_F(ButtonTest, DrawInvisibleButton)
{
    auto game = std::make_shared<MockGame>();
    ::testing::NiceMock<MockInput> input;
    EXPECT_CALL(*game, input()).WillRepeatedly(::testing::ReturnRef(input));
    b->setVisible(false);
    b->setGameInstance(game);
    b->update(0.1f);
    EXPECT_CALL(game->m_gfx, target()).Times(0);
    b->draw();
}

TEST_F(ButtonTest, DrawInActiveButton)
{
    auto game = std::make_shared<MockGame>();
    ::testing::NiceMock<MockInput> input;
    EXPECT_CALL(*game, input()).WillRepeatedly(::testing::ReturnRef(input));
    b->setActive(false);
    b->setGameInstance(game);
    b->update(0.1f);
    EXPECT_CALL(game->m_gfx, target()).Times(2);
    b->draw();
}

TEST_F(ButtonTest, CustomDrawable)
{
    auto game = std::make_shared<MockGame>();
    ::testing::NiceMock<MockInput> input;
    EXPECT_CALL(*game, input()).Times(2).WillRepeatedly(::testing::ReturnRef(input));
    b->setGameInstance(game);
    b->update(0.1f);

    auto d = std::make_shared<MockDrawable>();
    b->setDrawable(d);
    std::shared_ptr<jt::RenderTarget> renderTarget = nullptr;
    EXPECT_CALL(game->m_gfx, target()).Times(2);
    EXPECT_CALL(*d, setPosition(::testing::_));
    EXPECT_CALL(*d, update(0.1f));
    b->update(0.1f);
    EXPECT_CALL(*d, draw(renderTarget));
    b->draw();
    SUCCEED();
}

TEST_F(ButtonTest, IsNotActiveAfterSetInactive)
{
    b->setActive(false);
    ASSERT_FALSE(b->getActive());
}

TEST_F(ButtonTest, AddCallback)
{
    b->addCallback([]() {});
    ASSERT_EQ(b->getCallbackCount(), 1U);
}

TEST_F(ButtonTest, CallbacksAreEmptyAfterClearCallbacks)
{
    b->addCallback([]() {});
    b->clearCallbacks();
    ASSERT_EQ(b->getCallbackCount(), 0U);
}
