#include "box2d_world_impl.hpp"
#include "box2d_world_interface.hpp"
#include "conversions.hpp"
#include <gtest/gtest.h>

using namespace ::testing;

class Box2dWorldImplTest : public ::testing::Test {
public:
    void SetUp() override
    {
        wrapper = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2 { 0, 100.0f });
    }
    std::shared_ptr<jt::Box2DWorldImpl> wrapper;
};

TEST_F(Box2dWorldImplTest, CreateObject)
{
    b2BodyDef groundBodyDef;
    wrapper->createBody(&groundBodyDef);
}

TEST_F(Box2dWorldImplTest, DestroyObject)
{
    b2BodyDef groundBodyDef;
    auto body = wrapper->createBody(&groundBodyDef);
    wrapper->destroyBody(body);
}
