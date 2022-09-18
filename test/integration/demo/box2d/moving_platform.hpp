#ifndef MYAWESOMEGAME_MOVING_PLATFORM_HPP
#define MYAWESOMEGAME_MOVING_PLATFORM_HPP

#include <box2dwrapper/box2d_object.hpp>
#include <game_object.hpp>
#include <shape.hpp>
#include <memory>

class MovingPlatform : public jt::GameObject {
public:
    MovingPlatform(std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2f const& size,
        std::vector<jt::Vector2f> const& positions, float velocity);

private:
    std::shared_ptr<jt::Box2DObject> m_physicsObject;
    std::vector<jt::Vector2f> m_positions;
    float m_velocity { 1.0f };
    jt::Vector2f m_platformSize { 0.0f, 0.0f };

    // TODO replace with real graphics
    std::shared_ptr<jt::Shape> m_shape;

    bool m_movingForward { true };
    std::size_t m_currentIndex { 0 };
    float m_timeTilNextPlatform { 0.0f };
    jt::Vector2f m_currentVelocity { 0.0f, 0.0f };

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // MYAWESOMEGAME_MOVING_PLATFORM_HPP
