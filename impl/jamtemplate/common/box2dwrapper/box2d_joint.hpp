#ifndef JAMTEMPLATE_BOX2DJOINT_HPP
#define JAMTEMPLATE_BOX2DJOINT_HPP

#include <box2dwrapper/box2d_world_interface.hpp>
#include <conversions.hpp>
#include <game_object.hpp>
#include <vector.hpp>
#include <Box2D/Box2D.h>
#include <memory>

namespace jt {

/// RAII type Wrapper for a box2d Joint
class Box2DJoint : public GameObject {
public:
    using Sptr = std::shared_ptr<Box2DJoint>;
    Box2DJoint() = delete;

    /// Constructor
    ///
    /// \param world shared pointer to the world. Only a weak pointer to the world will be stored.
    /// \param def raw pointer to a joint definition
    Box2DJoint(std::shared_ptr<Box2DWorldInterface> world, const b2JointDef* def);

    /// Access function for the low level Box2D Joint
    /// \return pointer to the Box2D joint object
    b2Joint* getB2Joint() const;

private:
    // this pointer is NOT owning!
    // do never call delete on this
    b2Joint* m_joint { nullptr };

    std::weak_ptr<Box2DWorldInterface> m_world;

    void doDestroy() override;

    void setB2Joint(b2Joint* body);
};

} // namespace jt

#endif
