#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <animation.hpp>
#include <game_object.hpp>
#include <shape.hpp>
#include <memory>
#include <random>

class Object : public jt::GameObject {
public:
    using Sptr = std::shared_ptr<Object>;

    void Flash();
    void Shake();

    std::shared_ptr<jt::Animation> getAnimation();

private:
    std::shared_ptr<jt::Animation> m_animation;
    jt::Vector2f m_position;
    jt::Vector2f m_velocity;
    jt::Vector2f m_acceleration;

    void doCreate() override;
    void doUpdate(float const elapsed) override;

    void doDraw() const override;
};

#endif
