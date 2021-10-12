
#ifndef MYAWESOMEGAME_MOCK_CAMERA_HPP
#define MYAWESOMEGAME_MOCK_CAMERA_HPP

#include "cam_interface.hpp"
#include <gmock/gmock.h>

class MockCamera : public jt::CamInterface {
public:
    MOCK_METHOD(jt::Vector2, getCamOffset, (), (override));
    MOCK_METHOD(void, setCamOffset, (jt::Vector2 const&), (override));
    MOCK_METHOD(void, move, (jt::Vector2 const&), (override));
    MOCK_METHOD(float, getZoom, (), (const, override));
    MOCK_METHOD(void, setZoom, (float), (override));
    MOCK_METHOD(void, shake, (float, float, float), (override));
    MOCK_METHOD(jt::Vector2, getShakeOffset, (), (override));
    MOCK_METHOD(void, update, (float), (override));
    MOCK_METHOD(void, reset, (), (override));
};

#endif // MYAWESOMEGAME_MOCK_CAMERA_HPP
