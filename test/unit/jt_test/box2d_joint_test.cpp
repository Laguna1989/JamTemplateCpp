#include "box2dwrapper/box2d_joint.hpp"
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

TEST_F(Box2dJointTest, ConstructorCallsCreateJoint)
{
    EXPECT_CALL(*m_mockWorld, createJoint(nullptr));
    jt::Box2DJoint joint { m_mockWorld, nullptr };
}

TEST_F(Box2dJointTest, GetBodyReturnsNullptrWhenCreatedWithNullptrJointDef)
{
    jt::Box2DJoint joint { m_mockWorld, nullptr };
    EXPECT_EQ(joint.getB2Joint(), nullptr);
}

TEST_F(Box2dJointTest, Create)
{
    jt::Box2DJoint joint { m_mockWorld, nullptr };
    auto g = std::make_shared<MockGame>();

    joint.setGameInstance(g);
    joint.create();
    SUCCEED();
}

TEST_F(Box2dJointTest, Update)
{
    jt::Box2DJoint joint { m_mockWorld, nullptr };
    joint.update(1.0f);
    SUCCEED();
}

TEST_F(Box2dJointTest, Draw)
{
    jt::Box2DJoint joint { m_mockWorld, nullptr };
    joint.draw();
    SUCCEED();
}

TEST_F(Box2dJointTest, DestroyCallsDestroyJointOnWorld)
{
    jt::Box2DJoint joint { m_mockWorld, nullptr };

    EXPECT_CALL(*m_mockWorld, destroyJoint(_));
    joint.destroy();
}

TEST_F(Box2dJointTest, DestroyJointWithoutWorld)
{
    jt::Box2DJoint joint { m_mockWorld, nullptr };

    m_mockWorld.reset();
    joint.destroy();
}

TEST_F(Box2dJointTest, CreateJointWithNullptrWorldRaisesException)
{
    auto func = []() { jt::Box2DJoint joint { nullptr, nullptr }; };
    ASSERT_THROW(func(), std::invalid_argument);
}
