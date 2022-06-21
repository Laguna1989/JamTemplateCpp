#ifndef JAMTEMPLATE_MOCK_TWEEN_INTERFACE_HPP
#define JAMTEMPLATE_MOCK_TWEEN_INTERFACE_HPP

#include <tweens/tween_interface.hpp>
#include <gmock/gmock.h>

class MockTweenInterface : public jt::TweenInterface {
public:
    MOCK_METHOD(void, update, (float), (override));
    MOCK_METHOD(bool, isAlive, (), (const, override));
};

#endif // JAMTEMPLATE_MOCK_TWEEN_INTERFACE_HPP
