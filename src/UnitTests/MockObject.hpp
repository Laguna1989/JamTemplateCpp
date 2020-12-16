#ifndef JAMTEMPLATE_UNITTEST_MOCKOBJECT_HPP_INCLUDEGUARD
#define JAMTEMPLATE_UNITTEST_MOCKOBJECT_HPP_INCLUDEGUARD

#include "GameObject.hpp"
#include "gmock/gmock.h"

class MockObject : public jt::GameObject {
public:
    MOCK_METHOD(void, doUpdate, (float const), (override));
    MOCK_METHOD(void, doDraw, (), (const));
    MOCK_METHOD(void, doCreate, (), (override));
};

#endif
