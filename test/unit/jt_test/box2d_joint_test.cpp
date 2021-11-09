#include "box2d_joint.hpp"
#include "mocks/box2d_world_mock.hpp"
#include "mocks/mock_game.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

class Box2dJointTest : public ::testing::Test {
public:
    std::shared_ptr<Box2DWorldMock> m_mockWorld;

    void SetUp() override { m_mockWorld = std::make_shared<NiceMock<Box2DWorldMock>>(); }
};

TEST_F(Box2dJointTest, ConstructorCallsCreateBody)
{
    EXPECT_CALL(*m_mockWorld, createJoint(nullptr));
    jt::Box2DJoint obj { m_mockWorld, nullptr };
}

TEST_F(Box2dJointTest, GetBodyReturnsStoredPointer)
{
    jt::Box2DJoint obj { m_mockWorld, nullptr };
    EXPECT_EQ(obj.getB2Joint(), nullptr);
}

TEST_F(Box2dJointTest, Create)
{
    jt::Box2DJoint obj { m_mockWorld, nullptr };
    auto g = std::make_shared<MockGame>();

    obj.setGameInstance(g);
    obj.create();
    SUCCEED();
}

TEST_F(Box2dJointTest, Update)
{
    jt::Box2DJoint obj { m_mockWorld, nullptr };
    obj.update(1.0f);
    SUCCEED();
}

TEST_F(Box2dJointTest, Draw)
{
    jt::Box2DJoint obj { m_mockWorld, nullptr };
    obj.draw();
    SUCCEED();
}

TEST_F(Box2dJointTest, DestroyCallsDestroyBodyOnWorld)
{
    jt::Box2DJoint obj { m_mockWorld, nullptr };

    EXPECT_CALL(*m_mockWorld, destroyJoint(_));
    obj.destroy();
}
