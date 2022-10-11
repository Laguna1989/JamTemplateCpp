#ifndef JAMTEMPLATE_MOVING_PLATFORM_HPP
#define JAMTEMPLATE_MOVING_PLATFORM_HPP

#include "sprite.hpp"
#include <box2d/killbox.hpp>
#include <box2dwrapper/box2d_object.hpp>
#include <game_object.hpp>
#include <shape.hpp>
#include <memory>

class MovingPlatform : public jt::GameObject {
public:
    MovingPlatform(std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2f const& size,
        std::vector<std::pair<jt::Vector2f, float>> const& positions, float velocity,
        float timeoffset);

    void setLinkedKillbox(std::shared_ptr<Killbox> kb);

private:
    std::shared_ptr<jt::Box2DObject> m_physicsObject;
    std::vector<std::pair<jt::Vector2f, float>> m_positions;
    float m_velocity { 1.0f };
    float m_timeOffset { 0.0f };
    jt::Vector2f m_platformSize { 0.0f, 0.0f };
    mutable std::shared_ptr<jt::Sprite> m_spriteL { nullptr };
    mutable std::shared_ptr<jt::Sprite> m_spriteM { nullptr };
    mutable std::shared_ptr<jt::Sprite> m_spriteR { nullptr };

    bool m_movingForward { true };
    std::size_t m_currentIndex { 0 };
    float m_timeTilNextPlatform { 0.0f };
    jt::Vector2f m_currentVelocity { 0.0f, 0.0f };
    float m_waitTime { 0.0f };

    std::shared_ptr<Killbox> m_linkedKillbox { nullptr };
    jt::Vector2f m_linkedKillboxOffset { 0.0f, 0.0f };

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    bool moveFromTo(
        std::pair<jt::Vector2f, float> from, std::pair<jt::Vector2f, float> to, float elapsed);
};

#endif // JAMTEMPLATE_MOVING_PLATFORM_HPP
