#include "box2d_wrapper.hpp"
#include "conversions.hpp"
#include <gtest/gtest.h>

using namespace ::testing;

class Box2DWrapperTestFixture : public ::testing::Test {
public:
    void SetUp() override
    {
        world = std::make_shared<b2World>(b2Vec2 { 0, 100.0f });
        wrapper = std::make_shared<jt::Box2DWorldWrapper>(world);
    }
    std::shared_ptr<b2World> world;
    std::shared_ptr<jt::Box2DWorldWrapper> wrapper;
};

TEST_F(Box2DWrapperTestFixture, CreateObject)
{
    b2BodyDef groundBodyDef;
    wrapper->createBody(&groundBodyDef);
}

TEST_F(Box2DWrapperTestFixture, DestroyObject)
{
    b2BodyDef groundBodyDef;
    auto body = wrapper->createBody(&groundBodyDef);
    wrapper->destroyBody(body);
}

TEST_F(Box2DWrapperTestFixture, DestroyObjectWithouthWorld)
{
    b2BodyDef groundBodyDef;
    auto body = wrapper->createBody(&groundBodyDef);
    world.reset();
    wrapper->destroyBody(body);
}
