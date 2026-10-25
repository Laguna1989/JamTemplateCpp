#include <camera.hpp>
#include <camera_helpers.hpp>
#include <rect.hpp>
#include <vector.hpp>
#include <gtest/gtest.h>
#include <tuple>

namespace {
jt::Vector2f const screenSize { 400.0f, 300.0f };
} // namespace

class CameraHelpersTest : public ::testing::Test {
protected:
    jt::Camera cam { 1.0f };
};

TEST_F(CameraHelpersTest, CenterOnPlacesTargetInScreenCenter)
{
    jt::CameraHelpers::centerOn(cam, jt::Vector2f { 500.0f, 250.0f }, screenSize);

    jt::Vector2f const expected { 300.0f, 100.0f };
    ASSERT_EQ(cam.getCamOffset(), expected);
}

// target position on screen, expected camera movement (screen 400x300, margin 100, speed 90)
using FollowWithMarginParams = std::tuple<jt::Vector2f, jt::Vector2f>;

class CameraHelpersFollowWithMarginTest
    : public ::testing::TestWithParam<FollowWithMarginParams> {
protected:
    jt::Camera cam { 1.0f };
};

TEST_P(CameraHelpersFollowWithMarginTest, MovesCameraDependingOnDistanceToScreenEdges)
{
    auto const [targetOnScreen, expectedMovement] = GetParam();
    jt::Vector2f const initialOffset { 30.0f, -20.0f };
    cam.setCamOffset(initialOffset);

    jt::CameraHelpers::followWithMargin(cam, initialOffset + targetOnScreen, screenSize, 1.0f);

    ASSERT_EQ(cam.getCamOffset(), initialOffset + expectedMovement);
}

INSTANTIATE_TEST_SUITE_P(CameraHelpersFollowWithMarginTest, CameraHelpersFollowWithMarginTest,
    ::testing::Values(
        // inside dead zone
        FollowWithMarginParams { jt::Vector2f { 200.0f, 150.0f }, jt::Vector2f { 0.0f, 0.0f } },
        // exactly on the margin does not scroll
        FollowWithMarginParams { jt::Vector2f { 100.0f, 100.0f }, jt::Vector2f { 0.0f, 0.0f } },
        FollowWithMarginParams { jt::Vector2f { 300.0f, 200.0f }, jt::Vector2f { 0.0f, 0.0f } },
        // within margin: single speed
        FollowWithMarginParams { jt::Vector2f { 80.0f, 150.0f }, jt::Vector2f { -90.0f, 0.0f } },
        FollowWithMarginParams { jt::Vector2f { 50.0f, 150.0f }, jt::Vector2f { -90.0f, 0.0f } },
        FollowWithMarginParams { jt::Vector2f { 310.0f, 150.0f }, jt::Vector2f { 90.0f, 0.0f } },
        FollowWithMarginParams { jt::Vector2f { 200.0f, 80.0f }, jt::Vector2f { 0.0f, -90.0f } },
        FollowWithMarginParams { jt::Vector2f { 200.0f, 210.0f }, jt::Vector2f { 0.0f, 90.0f } },
        // within half margin: double speed
        FollowWithMarginParams { jt::Vector2f { 40.0f, 150.0f }, jt::Vector2f { -180.0f, 0.0f } },
        FollowWithMarginParams { jt::Vector2f { 360.0f, 150.0f }, jt::Vector2f { 180.0f, 0.0f } },
        FollowWithMarginParams { jt::Vector2f { 200.0f, 40.0f }, jt::Vector2f { 0.0f, -180.0f } },
        FollowWithMarginParams { jt::Vector2f { 200.0f, 260.0f }, jt::Vector2f { 0.0f, 180.0f } },
        // both axes
        FollowWithMarginParams { jt::Vector2f { 40.0f, 210.0f }, jt::Vector2f { -180.0f, 90.0f } },
        // off screen
        FollowWithMarginParams {
            jt::Vector2f { 500.0f, -100.0f }, jt::Vector2f { 180.0f, -180.0f } }));

TEST_F(CameraHelpersTest, FollowWithMarginScalesWithElapsed)
{
    jt::CameraHelpers::followWithMargin(cam, jt::Vector2f { 40.0f, 150.0f }, screenSize, 0.5f);

    jt::Vector2f const expected { -90.0f, 0.0f };
    ASSERT_EQ(cam.getCamOffset(), expected);
}

TEST_F(CameraHelpersTest, FollowWithMarginUsesCustomMarginAndSpeed)
{
    jt::CameraHelpers::followWithMargin(
        cam, jt::Vector2f { 15.0f, 150.0f }, screenSize, 1.0f, 20.0f, 10.0f);

    jt::Vector2f const expected { -10.0f, 0.0f };
    ASSERT_EQ(cam.getCamOffset(), expected);
}

// input offset, expected offset after clamping
using ClampParams = std::tuple<jt::Vector2f, jt::Vector2f>;

class CameraHelpersClampTest : public ::testing::TestWithParam<ClampParams> {
protected:
    jt::Camera cam { 1.0f };
    jt::Rectf const bounds { 0.0f, 0.0f, 1000.0f, 800.0f };
};

TEST_P(CameraHelpersClampTest, ClampKeepsViewInsideBounds)
{
    auto const [input, expected] = GetParam();
    cam.setCamOffset(input);

    jt::CameraHelpers::clampToBounds(cam, bounds, screenSize);

    ASSERT_EQ(cam.getCamOffset(), expected);
}

INSTANTIATE_TEST_SUITE_P(CameraHelpersClampTest, CameraHelpersClampTest,
    ::testing::Values(ClampParams { jt::Vector2f { 100.0f, 200.0f }, jt::Vector2f { 100.0f, 200.0f } },
        ClampParams { jt::Vector2f { -50.0f, -10.0f }, jt::Vector2f { 0.0f, 0.0f } },
        ClampParams { jt::Vector2f { 700.0f, 600.0f }, jt::Vector2f { 600.0f, 500.0f } },
        ClampParams { jt::Vector2f { 600.0f, 500.0f }, jt::Vector2f { 600.0f, 500.0f } },
        ClampParams { jt::Vector2f { -50.0f, 900.0f }, jt::Vector2f { 0.0f, 500.0f } }));

TEST_F(CameraHelpersTest, ClampWithOffsetBoundsRespectsBoundsOrigin)
{
    cam.setCamOffset(jt::Vector2f { 0.0f, 0.0f });

    jt::CameraHelpers::clampToBounds(cam, jt::Rectf { 100.0f, 50.0f, 1000.0f, 800.0f }, screenSize);

    jt::Vector2f const expected { 100.0f, 50.0f };
    ASSERT_EQ(cam.getCamOffset(), expected);
}

TEST_F(CameraHelpersTest, ClampCentersLevelSmallerThanScreen)
{
    cam.setCamOffset(jt::Vector2f { 123.0f, -45.0f });

    jt::CameraHelpers::clampToBounds(cam, jt::Rectf { 0.0f, 0.0f, 200.0f, 100.0f }, screenSize);

    jt::Vector2f const expected { -100.0f, -100.0f };
    ASSERT_EQ(cam.getCamOffset(), expected);
}

TEST_F(CameraHelpersTest, ClampCentersOnlyTheAxisThatIsSmallerThanScreen)
{
    cam.setCamOffset(jt::Vector2f { 2000.0f, 2000.0f });

    jt::CameraHelpers::clampToBounds(cam, jt::Rectf { 0.0f, 0.0f, 1000.0f, 100.0f }, screenSize);

    jt::Vector2f const expected { 600.0f, -100.0f };
    ASSERT_EQ(cam.getCamOffset(), expected);
}
