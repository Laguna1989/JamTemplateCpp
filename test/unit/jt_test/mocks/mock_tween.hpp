#ifndef JAMTEMPLATE_UNITTEST_MOCKTWEEN_HPP_INCLUDEGUARD
#define JAMTEMPLATE_UNITTEST_MOCKTWEEN_HPP_INCLUDEGUARD

#include "drawable_interface.hpp"
#include "tweens/tween_base.hpp"
#include <gmock/gmock.h>

class MockTween : public jt::Tween {
public:
    MockTween(std::weak_ptr<jt::DrawableInterface> obj, float totalTime)
        : jt::Tween { obj, totalTime }
    {
    }

    MOCK_METHOD(void, doUpdateObject, (std::shared_ptr<jt::DrawableInterface> const&, float),
        (const, override));
};

#endif
