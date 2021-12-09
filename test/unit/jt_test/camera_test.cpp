#include "camera.hpp"
#include "vector.hpp"
#include "gtest/gtest.h"

class CameraTest : public ::testing::Test {
protected:
    jt::Camera cam { 1.0f };
};

TEST_F(CameraTest, InitialCamOffset)
{
    jt::Vector2f const expected { 0.0f, 0.0f };
    ASSERT_EQ(cam.getCamOffset(), expected);
}

TEST_F(CameraTest, InitialShakeOffset)
{
    jt::Vector2f const expected { 0.0f, 0.0f };
    ASSERT_EQ(cam.getShakeOffset(), expected);
}
TEST_F(CameraTest, InitialZoom) { ASSERT_EQ(cam.getZoom(), 1); }

TEST_F(CameraTest, ZoomAfterSetZoom)
{
    float const expectedZoom1 { 10.0f };
    cam.setZoom(expectedZoom1);
    ASSERT_EQ(cam.getZoom(), expectedZoom1);
}

TEST_F(CameraTest, MoveChangesCamOffset)
{
    jt::Vector2f const cameraMovement { 3.5f, -10.0f };
    cam.move(cameraMovement);
    ASSERT_EQ(cam.getCamOffset(), cameraMovement);
}

TEST_F(CameraTest, SetCameraOffset)
{
    jt::Vector2f const newPosition { 9.99f, -20.0f };
    cam.setCamOffset(newPosition);
    ASSERT_EQ(cam.getCamOffset(), newPosition);
}

TEST_F(CameraTest, CamOffsetIsZeroAfterReset)
{
    cam.setCamOffset({ 222.0f, 241.5f });

    cam.reset();
    jt::Vector2f expectedPos { 0.0f, 0.0f };
    ASSERT_EQ(cam.getCamOffset(), expectedPos);
}

class CameraShakeIntervalTestFixture : public CameraTest,
                                       public ::testing::WithParamInterface<float> {
};

TEST_P(CameraShakeIntervalTestFixture, ShakeOffsetNotChangedBeforeShakeIntervallOver)
{
    float const shakeInterval = 0.5f;

    cam.shake(10, 1.0f, shakeInterval);
    cam.update(shakeInterval * GetParam());
    jt::Vector2f const initialShake { 0.0f, 0.0f };
    ASSERT_EQ(cam.getShakeOffset(), initialShake);
}

INSTANTIATE_TEST_SUITE_P(CameraShakeIntervalTest, CameraShakeIntervalTestFixture,
    ::testing::Values(0.0f, 0.1f, 0.5f, 0.9f, 0.99f));

TEST_F(CameraTest, ShakeOffsetChangedAfterShakeInterval)
{
    float const shakeInterval = 0.5f;

    cam.shake(10, 1.0f, shakeInterval);
    cam.update(shakeInterval * 1.01f);

    jt::Vector2f const initialShake { 0.0f, 0.0f };
    ASSERT_NE(cam.getShakeOffset(), initialShake);
}

TEST_F(CameraTest, ShakeOffsetIsAsSetByRandomFunction)
{
    float const shakeInterval = 0.5f;

    cam.setRandomFunction([](auto /*unused*/) { return 1.0f; });
    cam.shake(10, 1.0f, shakeInterval);
    cam.update(shakeInterval * 1.01f);

    jt::Vector2f const expectedShakeOffset { 1.0f, 1.0f };
    ASSERT_EQ(cam.getShakeOffset(), expectedShakeOffset);
}

TEST_F(CameraTest, ShakeOffsetBackToZeroAfterShakeTime)
{
    float const shakeTime = 10.0f;
    jt::Vector2f const initialShake { 0.0f, 0.0f };
    cam.shake(shakeTime, 1.0f, 0.1f);
    cam.update(shakeTime + 0.5f);
    ASSERT_EQ(cam.getShakeOffset(), initialShake);
}

TEST_F(CameraTest, ResetShakeOffset)
{
    float const shakeInterval = 0.5f;
    jt::Vector2f const initialShake { 0.0f, 0.0f };

    cam.shake(10, 1.0f, shakeInterval);
    cam.update(shakeInterval * 1.01f);

    cam.reset();
    ASSERT_EQ(cam.getShakeOffset(), initialShake);
}

TEST_F(CameraTest, NullptrRandomFunc)
{
    ASSERT_THROW(cam.setRandomFunction(nullptr), std::invalid_argument);
}
