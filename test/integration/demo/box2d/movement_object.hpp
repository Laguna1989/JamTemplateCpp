#ifndef STRESSTEST_MOVEMENTOBJECT_HPP
#define STRESSTEST_MOVEMENTOBJECT_HPP

#include <animation.hpp>
#include <box2dwrapper/box2d_object.hpp>
#include <memory>

class MovementObject : public jt::Box2DObject {
public:
    using Sptr = std::shared_ptr<MovementObject>;
    MovementObject(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

    ~MovementObject() = default;

    std::shared_ptr<jt::Animation> getAnimation();

private:
    std::shared_ptr<jt::Animation> m_animation;
    b2BodyType m_type;

    void doCreate() override;
    void doUpdate(float const elapsed) override;

    void doDraw() const override;
};

#endif
