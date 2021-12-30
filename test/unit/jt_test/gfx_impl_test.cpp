#include "camera.hpp"
#include "gfx_impl.hpp"
#include "render_window.hpp"
#include <gtest/gtest.h>

TEST(GfxImplTest, Reset)
{
    jt::RenderWindow window { 800, 600, "jt_tests" };
    jt::Camera cam { 1.0f };
    jt::GfxImpl gfx { std::move(window), std::move(cam) };
    EXPECT_NO_THROW(gfx.reset());
}

TEST(GfxImplTest, TextureManager)
{
    jt::RenderWindow window { 800, 600, "jt_tests" };
    jt::Camera cam { 1.0f };
    jt::GfxImpl gfx { std::move(window), std::move(cam) };
    EXPECT_NO_THROW(gfx.textureManager());
}
