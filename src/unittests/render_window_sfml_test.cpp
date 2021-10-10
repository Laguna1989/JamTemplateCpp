#include "render_window.hpp"
#include <gtest/gtest.h>

TEST(RenderWindowSFMLTest, GetMousePositionWithView)
{
    jt::RenderWindow rw { 100, 200, "test" };

    auto view = std::make_shared<sf::View>();
    rw.s_view = view;

    jt::Vector2 const expected { 0.0f, 0.0f };
    EXPECT_NE(rw.getMousePosition(), expected);
    rw.s_view.reset();
}
