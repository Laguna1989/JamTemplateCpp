#ifndef JAMTEMPLATE_BOX2D_WORLD_IMPL_HPP
#define JAMTEMPLATE_BOX2D_WORLD_IMPL_HPP

#include <box2dwrapper/box2d_contact_manager_interface.hpp>
#include <box2dwrapper/box2d_world_interface.hpp>
#include <vector.hpp>
#include <Box2D/Dynamics/b2World.h>
#include <memory>

namespace jt {

/// Implementation of the Box2DWorldInterface
class Box2DWorldImpl : public Box2DWorldInterface {
public:
    Box2DWorldImpl(jt::Vector2f const& gravity,
        std::shared_ptr<jt::Box2DContactManagerInterface> contactManager = nullptr);

    b2Body* createBody(const b2BodyDef* definition) override;

    void destroyBody(b2Body* body) override;

    b2Joint* createJoint(const b2JointDef* definition) override;

    void destroyJoint(b2Joint* joint) override;

    Box2DContactCallbackRegistryInterface& getContactManager() override;

    void step(float elapsed, int velocityIterations, int positionIterations) override;

private:
    std::unique_ptr<b2World> m_world { nullptr };
    std::shared_ptr<jt::Box2DContactManagerInterface> m_newContactManager { nullptr };
};

} // namespace jt
// namespace jt
#endif // JAMTEMPLATE_BOX2D_WORLD_IMPL_HPP
