#ifndef DEMO_SCENE_CIRCLE_TEST_HPP
#define DEMO_SCENE_CIRCLE_TEST_HPP

#include <game_object.hpp>
#include <shape.hpp>
#include <text.hpp>
#include <vector.hpp>
#include <memory>
#include <vector>

/// Mouse controlled circle tested against moving circles and rects via jt::Collision::CircleTest.
class SceneCircleTest : public jt::GameObject {
public:
    std::string getName() const override;

private:
    struct Obstacle {
        std::shared_ptr<jt::Shape> shape;
        jt::Vector2f velocity;
    };

    std::shared_ptr<jt::Shape> m_player { nullptr };
    std::vector<Obstacle> m_obstacles {};
    std::shared_ptr<jt::Text> m_info { nullptr };

    void doCreate() override;
    void doUpdate(float elapsed) override;
    void doDraw() const override;

    void moveObstacle(Obstacle& obstacle, float elapsed) const;
};

#endif // DEMO_SCENE_CIRCLE_TEST_HPP
