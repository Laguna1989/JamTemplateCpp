﻿#ifndef GUARD_JAMTEMPLATE_BOX2DOBJECT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_BOX2DOBJECT_HPP_INCLUDEGUARD

#include "Conversions.hpp"
#include "GameObject.hpp"
#include "vector.hpp"
#include <Box2D/Box2D.h>
#include <memory>

namespace jt {

class Box2DObject : public GameObject {
public:
    using Sptr = std::shared_ptr<Box2DObject>;
    Box2DObject() = delete;

    Box2DObject(std::shared_ptr<b2World> world, const b2BodyDef* def)
    {
        setB2Body(world->CreateBody(def));
    }

    jt::vector2 getPosition() const { return Conversion::vec(m_body->GetPosition()); }

    void setPosition(jt::vector2 p)
    {
        m_body->SetTransform(Conversion::vec(p), m_body->GetAngle());
    }

    float getRotation() const { return m_body->GetAngle(); }

    b2Body* getB2Body() { return m_body; }

private:
    // this pointer is NOT owning!
    // do never call delete on this
    b2Body* m_body { nullptr };

    void doUpdate(float const /*elapsed*/) override {};
    void doDraw() const override {};
    void doCreate() override {};

    void setB2Body(b2Body* body) { m_body = body; }
};
} // namespace jt
#endif
