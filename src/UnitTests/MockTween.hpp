#ifndef JAMTEMPLATE_UNITTEST_MOCKTWEEN_HPP_INCLUDEGUARD
#define JAMTEMPLATE_UNITTEST_MOCKTWEEN_HPP_INCLUDEGUARD

#include "TweenBase.hpp"
#include "gmock/gmock.h"

template <class T>
class MockTween : public jt::Tween<T> {
public:
    MockTween(std::weak_ptr<T> obj, typename jt::Tween<T>::OnUpdateCallbackType cb, float totalTime)
        : jt::Tween<T> { obj, cb, totalTime }
    {
    }

    MOCK_METHOD(void, doUpdate, (float const), (override));
};

#endif
