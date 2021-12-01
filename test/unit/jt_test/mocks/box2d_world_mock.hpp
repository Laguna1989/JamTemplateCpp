#ifndef GUARD_JAMTEMAPLTE_BOX2D_WORLD_MOCK_HPP
#define GUARD_JAMTEMAPLTE_BOX2D_WORLD_MOCK_HPP

#include "Box2D/Box2D.h"
#include "box2dwrapper/box2d_world_interface.hpp"
#include <gmock/gmock.h>

class Box2DWorldMock : public jt::Box2DWorldInterface {
public:
    MOCK_METHOD(b2Body*, createBody, (const b2BodyDef*), (override));
    MOCK_METHOD(void, destroyBody, (b2Body*), (override));
    MOCK_METHOD(b2Joint*, createJoint, (const b2JointDef*), (override));
    MOCK_METHOD(void, destroyJoint, (b2Joint*), (override));
    MOCK_METHOD(void, step, (float, int, int), (override));
    MOCK_METHOD(void, setContactListener, (std::shared_ptr<b2ContactListener>), (override));
};

#endif // GUARD_JAMTEMAPLTE_BOX2D_WORLD_MOCK_HPP
