#ifndef GUARD_JAMTEMPLATE_BOX2DOBJECT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_BOX2DOBJECT_HPP_INCLUDEGUARD

#include "box2d_wrapper.hpp"
#include "conversions.hpp"
#include "game_object.hpp"
#include "vector.hpp"
#include <Box2D/Box2D.h>
#include <memory>

namespace jt {

/// RAII type Wrapper for a box2d Object
class Box2DObject : public GameObject {
public:
    using Sptr = std::shared_ptr<Box2DObject>;
    Box2DObject() = delete;

    /// Constructor
    ///
    /// \param world shared pointer to the world
    /// \param def raw pointer to a body definition
    Box2DObject(std::shared_ptr<Box2DWorldInterface> world, const b2BodyDef* def);

    /// Get the position
    /// \return the position
    jt::Vector2 getPosition() const;

    /// Set the position (overwrite box2d simulation)
    /// \param position the new position
    void setPosition(Vector2 const& position);

    /// Get the velocity
    /// \return the velocity
    jt::Vector2 getVelocity() const;

    /// Set the velocity (overwrite box2d simulation)
    /// \param v the new velocity
    void setVelocity(Vector2 const& v);

    /// Set the rotation
    /// \return the rotation
    float getRotation() const;

    /// get the Box2d body pointer
    /// \return the pointer
    b2Body* getB2Body();

private:
    // this pointer is NOT owning!
    // do never call delete on this
    b2Body* m_body { nullptr };

    std::shared_ptr<Box2DWorldInterface> m_world { nullptr };

    void doCreate() override { }
    void doUpdate(float const /*elapsed*/) override { }
    void doDraw() const override { }

    void doDestroy() override;

    void setB2Body(b2Body* body);
};
} // namespace jt
#endif
