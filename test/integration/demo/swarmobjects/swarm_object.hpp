#ifndef STRESSTEST_SWARMOBJECT_HPP
#define STRESSTEST_SWARMOBJECT_HPP

#include <animation.hpp>
#include <game_interface.hpp>
#include <game_state.hpp>
#include <math_helper.hpp>
#include <random/random.hpp>
#include <memory>

class SwarmObject : public jt::GameObject {
public:
    using Sptr = std::shared_ptr<SwarmObject>;

    void doCreate() override;

    void setPosition(jt::Vector2f const& p);
    jt::Vector2f getPosition() const;

    void setVelocity(jt::Vector2f const& p);
    jt::Vector2f getVelocity() const;

    void setAcceleration(jt::Vector2f const& p);

private:
    std::shared_ptr<jt::Animation> m_animation;
    float m_swarmWeight = 0.0f;
    jt::Vector2f m_position { 0.0f, 0.0f };
    jt::Vector2f m_velocity { 0.0f, 0.0f };
    jt::Vector2f m_acceleration { 0.0f, 0.0f };

    void doUpdate(float const elapsed) override;

    void doDraw() const override;
};

#endif
