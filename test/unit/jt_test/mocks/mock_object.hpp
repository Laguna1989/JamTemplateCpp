#ifndef JAMTEMPLATE_UNITTEST_MOCKOBJECT_HPP
#define JAMTEMPLATE_UNITTEST_MOCKOBJECT_HPP

#include <game_object.hpp>
#include <gmock/gmock.h>

class MockObject : public jt::GameObject {
public:
    MOCK_METHOD(void, doUpdate, (float const), (override));
    MOCK_METHOD(void, doDraw, (), (const));
    MOCK_METHOD(void, doCreate, (), (override));
    MOCK_METHOD(void, doKill, (), (override));
    MOCK_METHOD(void, doDestroy, (), (override));
};

#endif
