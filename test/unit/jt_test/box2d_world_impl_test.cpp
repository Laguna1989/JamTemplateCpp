#include "box2dwrapper/box2d_world_impl.hpp"
#include "box2dwrapper/box2d_world_interface.hpp"
#include "conversions.hpp"
#include <gtest/gtest.h>

using namespace ::testing;

class Box2dWorldImplTest : public ::testing::Test {
public:
    void SetUp() override
    {
        wrapper = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0, 100.0f });
    }
    std::shared_ptr<jt::Box2DWorldImpl> wrapper;
};

TEST_F(Box2dWorldImplTest, CreateObject)
{
    b2BodyDef groundBodyDef;
    auto body = wrapper->createBody(&groundBodyDef);
    ASSERT_NE(body, nullptr);
}

TEST_F(Box2dWorldImplTest, DestroyObject)
{
    b2BodyDef groundBodyDef;
    auto body = wrapper->createBody(&groundBodyDef);
    wrapper->destroyBody(body);
}

TEST_F(Box2dWorldImplTest, CreateJoint)
{
    b2BodyDef groundBodyDef;
    auto bodya = wrapper->createBody(&groundBodyDef);
    auto bodyb = wrapper->createBody(&groundBodyDef);
    b2RevoluteJointDef def;
    def.Initialize(bodya, bodyb, b2Vec2_zero);
    auto joint = wrapper->createJoint(&def);
    ASSERT_NE(joint, nullptr);
}

TEST_F(Box2dWorldImplTest, DestroyJoint)
{
    b2BodyDef groundBodyDef;
    auto bodya = wrapper->createBody(&groundBodyDef);
    auto bodyb = wrapper->createBody(&groundBodyDef);
    b2RevoluteJointDef def;
    def.Initialize(bodya, bodyb, b2Vec2_zero);
    auto joint = wrapper->createJoint(&def);
    wrapper->destroyJoint(joint);
}

TEST_F(Box2dWorldImplTest, Step) { wrapper->step(0.1f, 1, 1); }
