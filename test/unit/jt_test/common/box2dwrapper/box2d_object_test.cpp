#include <box2dwrapper/box2d_object.hpp>
#include <box2dwrapper/box2d_world_impl.hpp>
#include <math_helper.hpp>
#include <mocks/box2d_world_mock.hpp>
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
    jt::Box2DObject obj { m_mockWorld, b2DefaultBodyDef() };
}

TEST_F(Box2dObjectTest, GetBodyIdReturnsIdFromWorld)
{
    b2BodyId const expectedId { 5, 1, 3 };
    ON_CALL(*m_mockWorld, createBody(_)).WillByDefault(Return(expectedId));
    jt::Box2DObject obj { m_mockWorld, b2DefaultBodyDef() };
    EXPECT_TRUE(B2_ID_EQUALS(obj.getBodyId(), expectedId));
}

TEST_F(Box2dObjectTest, DestroyCallsDestroyBodyOnWorld)
{
    auto obj = std::make_shared<jt::Box2DObject>(m_mockWorld, b2DefaultBodyDef());

    EXPECT_CALL(*m_mockWorld, destroyBody(_));
    obj.reset();
}

TEST_F(Box2dObjectTest, DestroyWithDeletedWorld)
{
    auto obj = std::make_shared<jt::Box2DObject>(m_mockWorld, b2DefaultBodyDef());

    m_mockWorld.reset();
    EXPECT_NO_THROW(obj.reset());
}

TEST(Box2dObjectNullWorldTest, CreateWithNullptrWorldRaisesException)
{
    auto func = []() { jt::Box2DObject obj { nullptr, b2DefaultBodyDef() }; };
    ASSERT_THROW(func(), std::invalid_argument);
}

class Box2dObjectWithWorldTest : public ::testing::Test {
public:
    std::shared_ptr<jt::Box2DWorldInterface> m_world;

    void SetUp() override { m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f {}); }

    std::shared_ptr<jt::Box2DObject> createDynamicObject()
    {
        auto def = b2DefaultBodyDef();
        def.type = b2_dynamicBody;
        auto obj = std::make_shared<jt::Box2DObject>(m_world, def);
        auto const shapeDef = b2DefaultShapeDef();
        auto const box = b2MakeBox(1.0f, 1.0f);
        b2CreatePolygonShape(obj->getBodyId(), &shapeDef, &box);
        return obj;
    }
};

TEST_F(Box2dObjectWithWorldTest, GetPositionReturnsSetPosition)
{
    auto obj = createDynamicObject();
    jt::Vector2f const newPosition { 2.0f, 17.0f };
    obj->setPosition(newPosition);
    ASSERT_EQ(obj->getPosition(), newPosition);
}

TEST_F(Box2dObjectWithWorldTest, GetVelocityReturnsSetVelocity)
{
    auto obj = createDynamicObject();
    jt::Vector2f const newVelocity { 3.0f, 13.0f };
    obj->setVelocity(newVelocity);
    ASSERT_EQ(obj->getVelocity(), newVelocity);
}

TEST_F(Box2dObjectWithWorldTest, GetVelocityReturnsAddedVelocity)
{
    auto obj = createDynamicObject();
    jt::Vector2f const newVelocity { 3.0f, 13.0f };
    obj->addVelocity(newVelocity);
    ASSERT_EQ(obj->getVelocity(), newVelocity);
}

TEST_F(Box2dObjectWithWorldTest, GetRotationReturnsValue)
{
    auto obj = createDynamicObject();
    auto const newRotation = jt::MathHelper::deg2rad(50.0f);
    b2Body_SetTransform(obj->getBodyId(), b2Vec2_zero, b2MakeRot(newRotation));
    ASSERT_NEAR(obj->getRotation(), 50.0f, 0.01f);
}

TEST_F(Box2dObjectWithWorldTest, SetPositionKeepsRotation)
{
    auto obj = createDynamicObject();
    b2Body_SetTransform(obj->getBodyId(), b2Vec2_zero, b2MakeRot(jt::MathHelper::deg2rad(30.0f)));
    auto const rotationBefore = b2Body_GetRotation(obj->getBodyId());
    obj->setPosition(jt::Vector2f { 5.0f, 5.0f });
    auto const rotationAfter = b2Body_GetRotation(obj->getBodyId());
    ASSERT_EQ(rotationAfter.c, rotationBefore.c);
    ASSERT_EQ(rotationAfter.s, rotationBefore.s);
}

TEST_F(Box2dObjectWithWorldTest, AddForceToCenter)
{
    auto obj = createDynamicObject();
    ASSERT_EQ(obj->getVelocity().x, 0.0f);
    obj->addForceToCenter(jt::Vector2f { 100.0f, 0.0f });
    m_world->step(0.01f, 4);
    ASSERT_NE(obj->getVelocity().x, 0.0f);
}

TEST_F(Box2dObjectWithWorldTest, IsEnabledByDefault)
{
    auto obj = createDynamicObject();
    ASSERT_TRUE(b2Body_IsEnabled(obj->getBodyId()));
}

TEST_F(Box2dObjectWithWorldTest, SetEnabledFalseDisablesBody)
{
    auto obj = createDynamicObject();
    obj->setEnabled(false);
    ASSERT_FALSE(b2Body_IsEnabled(obj->getBodyId()));
}

TEST_F(Box2dObjectWithWorldTest, SetEnabledTrueReenablesBody)
{
    auto obj = createDynamicObject();
    obj->setEnabled(false);
    obj->setEnabled(true);
    ASSERT_TRUE(b2Body_IsEnabled(obj->getBodyId()));
}

TEST_F(Box2dObjectWithWorldTest, DestroyRemovesBodyFromWorld)
{
    auto obj = createDynamicObject();
    auto const bodyId = obj->getBodyId();
    obj.reset();
    ASSERT_FALSE(b2Body_IsValid(bodyId));
}

TEST_F(Box2dObjectWithWorldTest, DestroyAfterWorldIsDestroyedDoesNotCrash)
{
    auto obj = createDynamicObject();
    m_world.reset();
    ASSERT_NO_FATAL_FAILURE(obj.reset());
}
