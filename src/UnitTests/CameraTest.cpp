#include "Camera.hpp"
#include "Vector.hpp"
#include "gtest/gtest.h"

TEST(CameraTest, InitialValues)
{
    jt::Camera cam {};
    EXPECT_EQ(cam.getCamOffset().x(), 0);
    EXPECT_EQ(cam.getCamOffset().y(), 0);

    EXPECT_EQ(cam.getShakeOffset().x(), 0);
    EXPECT_EQ(cam.getShakeOffset().y(), 0);

    EXPECT_EQ(cam.getZoom(), 1);
}

TEST(CameraTest, Zoom)
{
    jt::Camera cam {};
    ASSERT_EQ(cam.getZoom(), 1.0f);

    float const expectedZoom1 { 10.0f };
    cam.setZoom(expectedZoom1);
    EXPECT_EQ(cam.getZoom(), expectedZoom1);
}

TEST(CameraTest, Move)
{
    jt::Camera cam {};
    jt::Vector2 expectedPos { 0.0f, 0.0f };
    ASSERT_EQ(cam.getCamOffset(), expectedPos);

    jt::Vector2 const cameraMovement { 3.5f, -10.0f };
    cam.move(cameraMovement);
    expectedPos += cameraMovement;
    EXPECT_EQ(cam.getCamOffset(), expectedPos);
}

TEST(CameraTest, SetCameraOffset)
{
    jt::Camera cam {};
    jt::Vector2 expectedPos { 0.0f, 0.0f };
    ASSERT_EQ(cam.getCamOffset(), expectedPos);

    jt::Vector2 const newPosition { 9.99f, -20.0f };
    cam.setCamOffset(newPosition);
    expectedPos = newPosition;
    EXPECT_EQ(cam.getCamOffset(), expectedPos);
}

TEST(CameraTest, ResetCameraOffset)
{
    jt::Camera cam {};
    cam.setCamOffset({ 222.0f, 241.5f });
    jt::Vector2 expectedPos { 0.0f, 0.0f };
    ASSERT_NE(cam.getCamOffset(), expectedPos);

    cam.reset();
    EXPECT_EQ(cam.getCamOffset(), expectedPos);
}

TEST(CameraTest, ShakeOffsetNotChangedBeforeShakeIntervallOver)
{
    jt::Camera cam {};
    float const shakeInterval = 0.5f;
    jt::Vector2 const initialShake { 0.0f, 0.0f };
    ASSERT_EQ(cam.getShakeOffset(), initialShake);

    cam.shake(10, 1.0f, shakeInterval);
    EXPECT_EQ(cam.getShakeOffset(), initialShake);

    cam.update(shakeInterval / 2.0f);
    EXPECT_EQ(cam.getShakeOffset(), initialShake);

    cam.update(shakeInterval / 2.0f - shakeInterval * 0.1f);
    EXPECT_EQ(cam.getShakeOffset(), initialShake);
}

TEST(CameraTest, ShakeOffsetChangedAfterShakeInterval)
{
    jt::Camera cam {};
    float const shakeInterval = 0.5f;
    jt::Vector2 const initialShake { 0.0f, 0.0f };
    ASSERT_EQ(cam.getShakeOffset(), initialShake);

    cam.shake(10, 1.0f, shakeInterval);
    EXPECT_EQ(cam.getShakeOffset(), initialShake);

    cam.update(shakeInterval * 1.01f);
    EXPECT_NE(cam.getShakeOffset(), initialShake);
}

TEST(CameraTest, ShakeOffsetBackToZeroAfterShakeTime)
{
    jt::Camera cam {};
    float const shakeTime = 10.0f;
    float const shakeInterval = 0.1f;
    jt::Vector2 const initialShake { 0.0f, 0.0f };
    ASSERT_EQ(cam.getShakeOffset(), initialShake);

    cam.shake(shakeTime, 1.0f, shakeInterval);
    EXPECT_EQ(cam.getShakeOffset(), initialShake);

    cam.update(shakeTime);
    ASSERT_NE(cam.getShakeOffset(), initialShake);

    cam.update(1.1f);
    EXPECT_EQ(cam.getShakeOffset(), initialShake);
}

TEST(CameraTest, ResetShakeOffset)
{
    jt::Camera cam {};
    float const shakeInterval = 0.5f;
    jt::Vector2 const initialShake { 0.0f, 0.0f };

    cam.shake(10, 1.0f, shakeInterval);

    cam.update(shakeInterval * 1.01f);
    ASSERT_NE(cam.getShakeOffset(), initialShake);

    cam.reset();
    EXPECT_EQ(cam.getShakeOffset(), initialShake);
}
