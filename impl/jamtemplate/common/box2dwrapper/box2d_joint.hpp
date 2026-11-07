#pragma once

#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_object.hpp>
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
    /// \param def joint definition. Start from b2Default*JointDef().
    Box2DJoint(std::shared_ptr<Box2DWorldInterface> world, Box2DJointDef const& def);

    /// Access function for the low level Box2D Joint
    /// \return id of the Box2D joint
    b2JointId getJointId() const;

private:
    b2JointId m_jointId { b2_nullJointId };

    std::weak_ptr<Box2DWorldInterface> m_world;

    void doDestroy() override;
};

} // namespace jt
