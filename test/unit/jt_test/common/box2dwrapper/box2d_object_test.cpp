#include "box2dwrapper/box2d_world_impl.hpp"
#include "math_helper.hpp"
#include <box2dwrapper/box2d_object.hpp>
#include <mocks/box2d_world_mock.hpp>
#include <mocks/mock_game.hpp>
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
    SUCCEED();
}

TEST_F(Box2dObjectTest, DestroyCallsDestroyBodyOnWorld)
{
    auto obj = std::make_shared<jt::Box2DObject>(m_mockWorld, nullptr);

    EXPECT_CALL(*m_mockWorld, destroyBody(_));
    obj.reset();
}

TEST_F(Box2dObjectTest, DestroyWithDeletedWorld)
{
    auto obj = std::make_shared<jt::Box2DObject>(m_mockWorld, nullptr);

    m_mockWorld.reset();
    EXPECT_NO_THROW(obj.reset());
}

class Box2dObjectWithWorldTest : public ::testing::Test {
public:
    std::shared_ptr<jt::Box2DWorldInterface> m_world;

    void SetUp() override
    {
        m_world = std::make_shared<NiceMock<jt::Box2DWorldImpl>>(jt::Vector2f {});
    }

    jt::Box2DObject getBox2DObject()
    {
        b2BodyDef def {};
        def.type = b2_dynamicBody;
        return jt::Box2DObject { m_world, &def };
    }
};

TEST_F(Box2dObjectWithWorldTest, GetPositionReturnsSetPosition)
{
    auto obj = getBox2DObject();
    jt::Vector2f const newPosition { 2.0f, 17.0f };
    obj.setPosition(newPosition);
    ASSERT_EQ(obj.getPosition(), newPosition);
}

TEST_F(Box2dObjectWithWorldTest, GetVelocityReturnsSetVelocity)
{
    auto obj = getBox2DObject();
    jt::Vector2f const newVelocity { 3.0f, 13.0f };
    obj.setVelocity(newVelocity);
    ASSERT_EQ(obj.getVelocity(), newVelocity);
}

TEST_F(Box2dObjectWithWorldTest, GetVelocityReturnsAddedVelocity)
{
    auto obj = getBox2DObject();
    jt::Vector2f const newVelocity { 3.0f, 13.0f };
    obj.addVelocity(newVelocity);
    ASSERT_EQ(obj.getVelocity(), newVelocity);
}

TEST_F(Box2dObjectWithWorldTest, GetRotationReturnsValue)
{
    auto obj = getBox2DObject();
    auto const newRotation = jt::MathHelper::deg2rad(50.0f);
    obj.getB2Body()->SetTransform(b2Vec2_zero, newRotation);
    ASSERT_FLOAT_EQ(obj.getRotation(), 50.0f);
}

TEST_F(Box2dObjectWithWorldTest, AddForceToCenter)
{
    auto obj = getBox2DObject();
    ASSERT_EQ(obj.getB2Body()->GetLinearVelocity().x, 0.0f);
    obj.addForceToCenter(jt::Vector2f { 100.0f, 0.0f });
    m_world->step(0.01f, 10, 10);
    ASSERT_NE(obj.getB2Body()->GetLinearVelocity().x, 0.0f);
}
