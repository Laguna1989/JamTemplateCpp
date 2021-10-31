#ifndef JAMTEMPLATE_UNITTEST_MOCKTWEEN_HPP_INCLUDEGUARD
#define JAMTEMPLATE_UNITTEST_MOCKTWEEN_HPP_INCLUDEGUARD

#include "drawable_interface.hpp"
#include "tween_base.hpp"
#include <gmock/gmock.h>

class MockTween : public jt::Tween {
public:
    MockTween(std::weak_ptr<jt::DrawableInterface> obj, typename jt::Tween::OnUpdateCallbackType cb,
        float totalTime)
        : jt::Tween { obj, cb, totalTime }
    {
    }

    //    MOCK_METHOD(void, doUpdate, (float const), (override));
};

#endif
