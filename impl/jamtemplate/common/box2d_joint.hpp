#ifndef GUARD_JAMTEMPLATE_BOX2DOBJECT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_BOX2DOBJECT_HPP_INCLUDEGUARD

#include "game_object.hpp"
#include "box2d_wrapper.hpp"
#include "conversions.hpp"
#include "game_object.hpp"
#include "vector.hpp"
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
    /// \param world shared pointer to the world
    /// \param def raw pointer to a joint definition
    Box2DJoint(std::shared_ptr<Box2DWorldInterface> world, const b2JointDef* def);

private:
    // this pointer is NOT owning!
    // do never call delete on this
    b2Joint* m_joint { nullptr };

    std::shared_ptr<Box2DWorldInterface> m_world { nullptr };

    void doCreate() override { }
    void doUpdate(float const /*elapsed*/) override { }
    void doDraw() const override { }

    void doDestroy() override;

    void setB2Joint(b2Joint* body);
};
#endif
} // namespace jt
