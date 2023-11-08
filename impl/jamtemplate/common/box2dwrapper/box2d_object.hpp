#ifndef JAMTEMPLATE_BOX2DOBJECT_HPP
#define JAMTEMPLATE_BOX2DOBJECT_HPP

#include <box2dwrapper/box2d_world_interface.hpp>
#include <vector.hpp>
#include <memory>

class b2Body;

namespace jt {

/// RAII type Wrapper for a box2d Object
class Box2DObject {
public:
    using Sptr = std::shared_ptr<Box2DObject>;
    Box2DObject() = delete;

    /// Constructor
    ///
    /// \param world shared pointer to the world. Only a weak pointer will be stored.
    /// \param def raw pointer to a body definition
    Box2DObject(std::shared_ptr<Box2DWorldInterface> world, b2BodyDef const* def);

    virtual ~Box2DObject();

    /// Get position
    /// \return position
    jt::Vector2f getPosition() const;

    /// Set position (overwrite box2d simulation)
    /// \param position new position
    void setPosition(jt::Vector2f const& position);

    /// Get velocity
    /// \return velocity
    jt::Vector2f getVelocity() const;

    /// Set velocity (overwrite box2d simulation)
    /// \param v new velocity
    void setVelocity(jt::Vector2f const& v);

    /// Add velocity (overwrite box2d simulation)
    /// \param v velocity to be added
    void addVelocity(jt::Vector2f const& v);

    /// Add Force to center
    /// \param f force
    void addForceToCenter(Vector2f const& f);

    /// Get rotation in degree
    /// \return rotation in degree
    float getRotation() const;

    /// Get the low level Box2d body pointer
    /// \return the pointer
    b2Body* getB2Body();

private:
    // this pointer is NOT owning!
    // do never call delete on this
    b2Body* m_body { nullptr };

    std::weak_ptr<Box2DWorldInterface> m_world;

    void setB2Body(b2Body* body);
};

} // namespace jt
#endif
