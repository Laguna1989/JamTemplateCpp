#include "box2d_object.hpp"
#include "mocks/mock_game.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

class Box2DWorldMock : public jt::Box2DWorldInterface {
public:
    MOCK_METHOD(b2Body*, createBody, (const b2BodyDef*), (override));
    MOCK_METHOD(void, destroyBody, (b2Body*), (override));
};

TEST(Box2DObjectTest, ConstructorCallsCreateBody)
{
    auto mock = std::make_shared<Box2DWorldMock>();
    EXPECT_CALL(*mock, createBody(_));
    jt::Box2DObject obj { mock, nullptr };
}

TEST(Box2DObjectTest, getBodyReturnsStoredPointer)
{
    auto mock = std::make_shared<::testing::NiceMock<Box2DWorldMock>>();
    jt::Box2DObject obj { mock, nullptr };
    EXPECT_EQ(obj.getB2Body(), nullptr);
}

TEST(Box2DObjectTest, create)
{
    auto mock = std::make_shared<::testing::NiceMock<Box2DWorldMock>>();
    jt::Box2DObject obj { mock, nullptr };
    auto g = std::make_shared<MockGame>();

    obj.setGameInstance(g);
    obj.create();
    SUCCEED();
}

TEST(Box2DObjectTest, update)
{
    auto mock = std::make_shared<::testing::NiceMock<Box2DWorldMock>>();
    jt::Box2DObject obj { mock, nullptr };
    obj.update(1.0f);
    SUCCEED();
}

TEST(Box2DObjectTest, draw)
{
    auto mock = std::make_shared<::testing::NiceMock<Box2DWorldMock>>();
    jt::Box2DObject obj { mock, nullptr };
    obj.draw();
    SUCCEED();
}

TEST(Box2DObjectTest, DestroyCallsDestroyBodyOnWorld)
{
    auto mock = std::make_shared<::testing::NiceMock<Box2DWorldMock>>();
    jt::Box2DObject obj { mock, nullptr };

    EXPECT_CALL(*mock, destroyBody(_));
    obj.destroy();
}
