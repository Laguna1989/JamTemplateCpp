#include <camera.hpp>
#include <gfx_impl.hpp>
#include <graphics/render_window.hpp>
#include <mocks/mock_camera.hpp>
#include <gtest/gtest.h>

TEST(GfxImplTest, Reset)
{
    jt::RenderWindow window { 800, 600, "jt_tests" };
    jt::Camera cam { 1.0f };
    jt::GfxImpl gfx { window, cam };
    ASSERT_NO_THROW(gfx.reset());
}

TEST(GfxImplTest, TextureManager)
{
    jt::RenderWindow window { 800, 600, "jt_tests" };
    jt::Camera cam { 1.0f };
    jt::GfxImpl gfx { window, cam };
    ASSERT_NO_THROW(gfx.textureManager());
}

TEST(GfxImplTest, WindowReturnsCorrectWindow)
{
    jt::RenderWindow window { 800, 600, "jt_tests" };
    jt::Camera cam { 1.0f };
    jt::GfxImpl gfx { window, cam };
    ASSERT_EQ(&gfx.window(), &window);
}

TEST(GfxImplTest, CameraReturnsCorrectCamera)
{
    jt::RenderWindow window { 800, 600, "jt_tests" };
    jt::Camera cam { 1.0f };
    jt::GfxImpl gfx { window, cam };
    ASSERT_EQ(&gfx.camera(), &cam);
}

TEST(GfxImplTest, TargetReturnsNoNullptr)
{
    jt::RenderWindow window { 800, 600, "jt_tests" };
    jt::Camera cam { 1.0f };
    jt::GfxImpl gfx { window, cam };
    ASSERT_NE(gfx.target(), nullptr);
}

TEST(GfxImplTest, UpdateCallUpdateOnCamera)
{
    jt::RenderWindow window { 800, 600, "jt_tests" };
    ::testing::NiceMock<MockCamera> cam {};
    jt::GfxImpl gfx { window, cam };
    EXPECT_CALL(cam, update(1.0f));

    gfx.update(1.0f);
}

TEST(GfxImplTest, ClearDoesNotThrow)
{
    jt::RenderWindow window { 800, 600, "jt_tests" };
    jt::Camera cam {};
    jt::GfxImpl gfx { window, cam };

    ASSERT_NO_THROW(gfx.clear());
}

#if USE_SFML

TEST(GfxImplTest, DisplayDoesNotThrow)
{
    jt::RenderWindow window { 800, 600, "jt_tests" };
    jt::Camera cam {};
    jt::GfxImpl gfx { window, cam };

    ASSERT_NO_THROW(gfx.display());
}

#endif
