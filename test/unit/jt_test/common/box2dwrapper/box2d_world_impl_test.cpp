#include <box2dwrapper/box2d_world_impl.hpp>
#include <gtest/gtest.h>
#include <memory>

class Box2dWorldImplTest : public ::testing::Test {
public:
    void SetUp() override
    {
        world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0, 100.0f });
    }
    std::shared_ptr<jt::Box2DWorldImpl> world;

    b2BodyId createBox(b2BodyType type, jt::Vector2f const& position, b2ShapeDef const& shapeDef)
    {
        auto bodyDef = b2DefaultBodyDef();
        bodyDef.type = type;
        bodyDef.position = b2Vec2 { position.x, position.y };
        auto const body = world->createBody(bodyDef);
        auto const box = b2MakeBox(1.0f, 1.0f);
        b2CreatePolygonShape(body, &shapeDef, &box);
        return body;
    }
};

TEST_F(Box2dWorldImplTest, WorldIdIsValid) { ASSERT_TRUE(b2World_IsValid(world->getWorldId())); }

TEST_F(Box2dWorldImplTest, WorldIsDestroyedWithImpl)
{
    auto const worldId = world->getWorldId();
    world.reset();
    ASSERT_FALSE(b2World_IsValid(worldId));
}

TEST_F(Box2dWorldImplTest, GravityIsPassedToWorld)
{
    auto const gravity = b2World_GetGravity(world->getWorldId());
    ASSERT_FLOAT_EQ(gravity.x, 0.0f);
    ASSERT_FLOAT_EQ(gravity.y, 100.0f);
}

TEST(Box2dWorldImplWorldDefTest, WorldDefIsPassedToWorld)
{
    auto worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2 { 3.0f, -7.0f };
    worldDef.enableSleep = false;
    jt::Box2DWorldImpl const world { worldDef };

    auto const gravity = b2World_GetGravity(world.getWorldId());
    ASSERT_FLOAT_EQ(gravity.x, 3.0f);
    ASSERT_FLOAT_EQ(gravity.y, -7.0f);
    ASSERT_FALSE(b2World_IsSleepingEnabled(world.getWorldId()));
}

TEST_F(Box2dWorldImplTest, CreateBodyReturnsValidBody)
{
    auto const body = world->createBody(b2DefaultBodyDef());
    ASSERT_TRUE(b2Body_IsValid(body));
}

TEST_F(Box2dWorldImplTest, DestroyBodyInvalidatesBody)
{
    auto const body = world->createBody(b2DefaultBodyDef());
    world->destroyBody(body);
    ASSERT_FALSE(b2Body_IsValid(body));
}

TEST_F(Box2dWorldImplTest, DestroyBodyTwiceDoesNotCrash)
{
    auto const body = world->createBody(b2DefaultBodyDef());
    world->destroyBody(body);
    ASSERT_NO_FATAL_FAILURE(world->destroyBody(body));
}

TEST_F(Box2dWorldImplTest, CreateJointReturnsValidJointForEveryJointType)
{
    auto const bodyA = world->createBody(b2DefaultBodyDef());
    auto bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    auto const bodyB = world->createBody(bodyDef);

    auto withBodies = [&](auto def) {
        def.base.bodyIdA = bodyA;
        def.base.bodyIdB = bodyB;
        return jt::Box2DJointDef { def };
    };

    std::vector<jt::Box2DJointDef> const definitions { withBodies(b2DefaultDistanceJointDef()),
        withBodies(b2DefaultFilterJointDef()), withBodies(b2DefaultMotorJointDef()),
        withBodies(b2DefaultPrismaticJointDef()), withBodies(b2DefaultRevoluteJointDef()),
        withBodies(b2DefaultWeldJointDef()), withBodies(b2DefaultWheelJointDef()) };

    for (auto const& def : definitions) {
        auto const joint = world->createJoint(def);
        ASSERT_TRUE(b2Joint_IsValid(joint)) << "joint variant index " << def.index();
    }
}

TEST_F(Box2dWorldImplTest, DestroyJointInvalidatesJoint)
{
    auto const bodyA = world->createBody(b2DefaultBodyDef());
    auto const bodyB = world->createBody(b2DefaultBodyDef());
    auto def = b2DefaultRevoluteJointDef();
    def.base.bodyIdA = bodyA;
    def.base.bodyIdB = bodyB;
    auto const joint = world->createJoint(def);
    world->destroyJoint(joint);
    ASSERT_FALSE(b2Joint_IsValid(joint));
}

TEST_F(Box2dWorldImplTest, StepMovesDynamicBodyAlongGravity)
{
    auto const body = createBox(b2_dynamicBody, jt::Vector2f { 0.0f, 0.0f }, b2DefaultShapeDef());
    world->step(0.1f, 4);
    ASSERT_GT(b2Body_GetPosition(body).y, 0.0f);
}

TEST_F(Box2dWorldImplTest, NoContactEventsWithoutOptIn)
{
    createBox(b2_staticBody, jt::Vector2f { 0.0f, 5.0f }, b2DefaultShapeDef());
    createBox(b2_dynamicBody, jt::Vector2f { 0.0f, 0.0f }, b2DefaultShapeDef());

    int beginCount = 0;
    for (int i = 0; i != 120; ++i) {
        world->step(1.0f / 60.0f, 4);
        beginCount += world->getContactEvents().beginCount;
    }
    ASSERT_EQ(beginCount, 0);
}

TEST_F(Box2dWorldImplTest, ContactBeginEventIsReportedForOptedInShapes)
{
    auto shapeDef = b2DefaultShapeDef();
    shapeDef.enableContactEvents = true;
    createBox(b2_staticBody, jt::Vector2f { 0.0f, 5.0f }, shapeDef);
    createBox(b2_dynamicBody, jt::Vector2f { 0.0f, 0.0f }, shapeDef);

    int beginCount = 0;
    for (int i = 0; i != 120; ++i) {
        world->step(1.0f / 60.0f, 4);
        beginCount += world->getContactEvents().beginCount;
    }
    ASSERT_EQ(beginCount, 1);
}

TEST_F(Box2dWorldImplTest, SensorDetectsOptedInShape)
{
    auto sensorDef = b2DefaultShapeDef();
    sensorDef.isSensor = true;
    sensorDef.enableSensorEvents = true;
    auto const sensorBody = createBox(b2_dynamicBody, jt::Vector2f { 0.0f, 0.0f }, sensorDef);

    auto visitorDef = b2DefaultShapeDef();
    visitorDef.enableSensorEvents = true;
    createBox(b2_staticBody, jt::Vector2f { 0.5f, 0.0f }, visitorDef);

    world->step(1.0f / 60.0f, 4);

    b2ShapeId sensorShape {};
    b2Body_GetShapes(sensorBody, &sensorShape, 1);
    ASSERT_EQ(b2Shape_GetSensorCapacity(sensorShape), 1);
    ASSERT_EQ(world->getSensorEvents().beginCount, 1);
}

TEST_F(Box2dWorldImplTest, SensorIgnoresShapeWithoutOptIn)
{
    auto sensorDef = b2DefaultShapeDef();
    sensorDef.isSensor = true;
    sensorDef.enableSensorEvents = true;
    auto const sensorBody = createBox(b2_dynamicBody, jt::Vector2f { 0.0f, 0.0f }, sensorDef);

    createBox(b2_staticBody, jt::Vector2f { 0.5f, 0.0f }, b2DefaultShapeDef());

    world->step(1.0f / 60.0f, 4);

    b2ShapeId sensorShape {};
    b2Body_GetShapes(sensorBody, &sensorShape, 1);
    ASSERT_EQ(b2Shape_GetSensorCapacity(sensorShape), 0);
    ASSERT_EQ(world->getSensorEvents().beginCount, 0);
}
