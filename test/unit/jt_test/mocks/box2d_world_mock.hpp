#ifndef JAMTEMPLATE_BOX2D_WORLD_MOCK_HPP
#define JAMTEMPLATE_BOX2D_WORLD_MOCK_HPP

#include <box2dwrapper/box2d_world_interface.hpp>
#include <gmock/gmock.h>

class Box2DWorldMock : public jt::Box2DWorldInterface {
public:
    MOCK_METHOD(b2BodyId, createBody, (b2BodyDef const&), (override));
    MOCK_METHOD(void, destroyBody, (b2BodyId), (override));
    MOCK_METHOD(b2JointId, createJoint, (jt::Box2DJointDef const&), (override));
    MOCK_METHOD(void, destroyJoint, (b2JointId), (override));
    MOCK_METHOD(void, step, (float, int), (override));
    MOCK_METHOD(b2ContactEvents, getContactEvents, (), (const, override));
    MOCK_METHOD(b2SensorEvents, getSensorEvents, (), (const, override));
    MOCK_METHOD(b2WorldId, getWorldId, (), (const, override));
};

#endif // JAMTEMPLATE_BOX2D_WORLD_MOCK_HPP
