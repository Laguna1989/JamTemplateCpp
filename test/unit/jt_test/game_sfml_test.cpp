#include "game_test.hpp"
#include "mocks/mock_state.hpp"
#include "rect.hpp"
#include "render_window.hpp"

// TODO clean up usage of sf::view

TEST_F(GameTest, UpdateWithView)
{
    auto ms = std::make_shared<MockState>();
    EXPECT_CALL(*ms, doInternalCreate());
    g->switchState(ms);

    auto view = std::make_shared<sf::View>(jt::Rect(0, 0, 100.0f, 50.0f));
    view->setViewport(jt::Rect { 0, 0, 1.0f, 1.0f });
    g->setView(view);

    float expected_update_time = 0.05f;
    EXPECT_CALL(*ms, doInternalUpdate(expected_update_time));
    g->update(expected_update_time);
}

TEST_F(GameTest, SetViewWithRenderTarget)
{
    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillRepeatedly(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    ASSERT_NE(g->getRenderTarget(), nullptr);

    g->setView(g->getView());

    // cleanup so that future tests are not affected!
    jt::RenderWindow::s_view = std::shared_ptr<sf::View> { nullptr };
}

TEST_F(GameTest, SetupRenderTarget)
{
    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillOnce(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    ASSERT_FLOAT_EQ(g->getView()->getSize().x, 20.0f);
    ASSERT_FLOAT_EQ(g->getView()->getSize().y, 40.0f);

    // cleanup so that future tests are not affected!
    jt::RenderWindow::s_view = std::shared_ptr<sf::View> { nullptr };
}

TEST_F(GameTest, SetupRenderTargetWithZoom)
{
    EXPECT_CALL(*camera, getZoom()).WillOnce(::testing::Return(2.0f));

    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillOnce(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    ASSERT_FLOAT_EQ(g->getView()->getSize().x, 10.0f);
    ASSERT_FLOAT_EQ(g->getView()->getSize().y, 20.0f);

    // cleanup so that future tests are not affected!
    jt::RenderWindow::s_view = std::shared_ptr<sf::View> { nullptr };
}

TEST_F(GameTest, SetRenderTarget)
{
    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillOnce(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    ASSERT_NE(g->getRenderTarget(), nullptr);

    g->setRenderTarget(g->getRenderTarget());

    // cleanup so that future tests are not affected!
    jt::RenderWindow::s_view = std::shared_ptr<sf::View> { nullptr };
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

    // cleanup so that future tests are not affected!
    jt::RenderWindow::s_view = std::shared_ptr<sf::View> { nullptr };
}
