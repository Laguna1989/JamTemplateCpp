#include "Box2DObject.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

class Box2DWorldMock : public Box2DWorldInterface {
public:
    MOCK_METHOD(b2Body*, CreateBody, (const b2BodyDef*), (override));
    MOCK_METHOD(void, DestroyBody, (b2Body*), (override));
};

TEST(Box2DObjectTest, ConstructorCallsCreateBody)
{
    auto mock = std::make_shared<Box2DWorldMock>();
    EXPECT_CALL(*mock, CreateBody(_));
    jt::Box2DObject b2dobj { mock, nullptr };
}
