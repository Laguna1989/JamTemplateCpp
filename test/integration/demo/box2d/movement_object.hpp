#ifndef STRESSTEST_MOVEMENTOBJECT_HPP
#define STRESSTEST_MOVEMENTOBJECT_HPP

#include <animation.hpp>
#include <box2dwrapper/box2d_object.hpp>
#include <game_object.hpp>
#include <Box2D/Box2D.h>
#include <memory>

class Player : public jt::GameObject {
public:
    using Sptr = std::shared_ptr<Player>;
    Player(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

    ~Player() = default;

    std::shared_ptr<jt::Animation> getAnimation();

private:
    std::shared_ptr<jt::Animation> m_animation;
    std::shared_ptr<jt::Box2DObject> m_physicsObject;
    b2BodyType m_type;

    void doCreate() override;
    void doUpdate(float const elapsed) override;

    void doDraw() const override;
};

#endif
