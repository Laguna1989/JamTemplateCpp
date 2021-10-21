#include "game_test.hpp"
#include "mocks/mock_state.hpp"
#include "rect.hpp"
#include "render_window.hpp"

TEST_F(GameTest, SetupRenderTarget)
{
    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillOnce(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    ASSERT_EQ(g->getRenderTarget()->getSize().x, 20);
    ASSERT_EQ(g->getRenderTarget()->getSize().y, 40);
}

TEST_F(GameTest, SetupRenderTargetWithZoom)
{
    EXPECT_CALL(*camera, getZoom()).WillOnce(::testing::Return(2.0f));

    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillOnce(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    ASSERT_EQ(g->getRenderTarget()->getSize().x, 10);
    ASSERT_EQ(g->getRenderTarget()->getSize().y, 20);
}

TEST_F(GameTest, SetRenderTarget)
{
    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillOnce(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    ASSERT_NE(g->getRenderTarget(), nullptr);

    g->setRenderTarget(g->getRenderTarget());
}
TEST_F(GameTest, DrawWithRenderTargetAndState)
{
    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillRepeatedly(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    ASSERT_NE(g->getRenderTarget(), nullptr);

    auto ms = std::make_shared<MockState>();
    EXPECT_CALL(*ms, doInternalCreate());
    g->switchState(ms);

    EXPECT_CALL(*ms, doInternalUpdate(0.1f));
    g->update(0.1f);
    EXPECT_CALL(*ms, doInternalDraw());
    g->draw();
}
