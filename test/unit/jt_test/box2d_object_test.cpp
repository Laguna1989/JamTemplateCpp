#include "box2dwrapper/box2d_object.hpp"
#include "mocks/box2d_world_mock.hpp"
#include "mocks/mock_game.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

class Box2dObjectTest : public ::testing::Test {
public:
    std::shared_ptr<Box2DWorldMock> m_mockWorld;

    void SetUp() override { m_mockWorld = std::make_shared<NiceMock<Box2DWorldMock>>(); }
};

TEST_F(Box2dObjectTest, ConstructorCallsCreateBody)
{
    EXPECT_CALL(*m_mockWorld, createBody(_));
    jt::Box2DObject obj { m_mockWorld, nullptr };
}

TEST_F(Box2dObjectTest, GetBodyReturnsStoredPointer)
{
    jt::Box2DObject obj { m_mockWorld, nullptr };
    EXPECT_EQ(obj.getB2Body(), nullptr);
}

TEST_F(Box2dObjectTest, Create)
{
    jt::Box2DObject obj { m_mockWorld, nullptr };
    auto g = std::make_shared<MockGame>();

    obj.setGameInstance(g);
    obj.create();
    SUCCEED();
}

TEST_F(Box2dObjectTest, Update)
{
    jt::Box2DObject obj { m_mockWorld, nullptr };
    obj.update(1.0f);
    SUCCEED();
}

TEST_F(Box2dObjectTest, Draw)
{
    jt::Box2DObject obj { m_mockWorld, nullptr };
    obj.draw();
    SUCCEED();
}

TEST_F(Box2dObjectTest, DestroyCallsDestroyBodyOnWorld)
{
    jt::Box2DObject obj { m_mockWorld, nullptr };

    EXPECT_CALL(*m_mockWorld, destroyBody(_));
    obj.destroy();
}
