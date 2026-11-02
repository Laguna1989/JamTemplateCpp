#include <box2dwrapper/box2d_joint.hpp>
#include <box2dwrapper/box2d_world_impl.hpp>
#include <mocks/box2d_world_mock.hpp>
#include <mocks/mock_game.hpp>
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
    EXPECT_CALL(*m_mockWorld, createJoint(_));
    jt::Box2DJoint joint { m_mockWorld, b2DefaultRevoluteJointDef() };
}

TEST_F(Box2dJointTest, GetJointIdReturnsIdFromWorld)
{
    b2JointId const expectedId { 7, 1, 2 };
    ON_CALL(*m_mockWorld, createJoint(_)).WillByDefault(Return(expectedId));
    jt::Box2DJoint joint { m_mockWorld, b2DefaultRevoluteJointDef() };
    EXPECT_TRUE(B2_ID_EQUALS(joint.getJointId(), expectedId));
}

TEST_F(Box2dJointTest, Create)
{
    jt::Box2DJoint joint { m_mockWorld, b2DefaultRevoluteJointDef() };
    auto g = std::make_shared<MockGame>();

    joint.setGameInstance(g);
    joint.create();
    SUCCEED();
}

TEST_F(Box2dJointTest, Update)
{
    jt::Box2DJoint joint { m_mockWorld, b2DefaultRevoluteJointDef() };
    joint.update(1.0f);
    SUCCEED();
}

TEST_F(Box2dJointTest, Draw)
{
    jt::Box2DJoint joint { m_mockWorld, b2DefaultRevoluteJointDef() };
    joint.draw();
    SUCCEED();
}

TEST_F(Box2dJointTest, DestroyCallsDestroyJointOnWorld)
{
    jt::Box2DJoint joint { m_mockWorld, b2DefaultRevoluteJointDef() };

    EXPECT_CALL(*m_mockWorld, destroyJoint(_));
    joint.destroy();
}

TEST_F(Box2dJointTest, DestroyJointWithoutWorld)
{
    jt::Box2DJoint joint { m_mockWorld, b2DefaultRevoluteJointDef() };

    m_mockWorld.reset();
    joint.destroy();
}

TEST_F(Box2dJointTest, CreateJointWithNullptrWorldRaisesException)
{
    auto func = []() { jt::Box2DJoint joint { nullptr, b2DefaultRevoluteJointDef() }; };
    ASSERT_THROW(func(), std::invalid_argument);
}

TEST(Box2dJointWithWorldTest, DestroyJointAfterBodyWasDestroyedDoesNotCrash)
{
    auto world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f {});
    auto const bodyDef = b2DefaultBodyDef();
    auto const bodyA = world->createBody(bodyDef);
    auto const bodyB = world->createBody(bodyDef);

    auto jointDef = b2DefaultWeldJointDef();
    jointDef.base.bodyIdA = bodyA;
    jointDef.base.bodyIdB = bodyB;
    jt::Box2DJoint joint { world, jointDef };

    // destroying a body also destroys all attached joints
    world->destroyBody(bodyA);
    ASSERT_NO_FATAL_FAILURE(joint.destroy());
}
