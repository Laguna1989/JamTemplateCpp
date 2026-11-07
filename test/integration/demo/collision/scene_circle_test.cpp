#include "scene_circle_test.hpp"
#include <collision.hpp>
#include <drawable_helpers.hpp>
#include <random/random.hpp>
#include <string>

namespace {
constexpr jt::Vector2f screenSize { 400.0f, 300.0f };
constexpr jt::Color obstacleColor { 80, 120, 200 };
constexpr jt::Color hitColor { 230, 60, 60 };
constexpr int numberOfObstacles { 16 };
} // namespace

void SceneCircleTest::doCreate()
{
    m_player = jt::dh::createShapeCircle(12.0f, jt::colors::White, textureManager());
    m_player->setOrigin(jt::OriginMode::CENTER);

    for (auto i = 0; i != numberOfObstacles; ++i) {
        std::shared_ptr<jt::Shape> shape { nullptr };
        if (i % 2 == 0) {
            shape = jt::dh::createShapeCircle(
                jt::Random::getFloat(6.0f, 20.0f), obstacleColor, textureManager());
        } else {
            // Rects are tested with a radius averaged from width and height. Elongated rects
            // show where this approximation reports hits outside the rect or misses its corners.
            shape = jt::dh::createShapeRect(jt::Vector2f { jt::Random::getFloat(10.0f, 60.0f),
                                                jt::Random::getFloat(10.0f, 40.0f) },
                obstacleColor, textureManager());
        }
        shape->setOrigin(jt::OriginMode::CENTER);
        shape->setPosition(jt::Random::getRandomPointIn(jt::Rectf { 40.0f, 40.0f, 320.0f, 220.0f }));
        m_obstacles.push_back(Obstacle { shape, jt::Random::getRandomPointInCircle(40.0f) });
    }

    m_info = jt::dh::createText(renderTarget(), "", 12);
    m_info->setTextAlign(jt::Text::TextAlign::LEFT);
    m_info->setPosition(jt::Vector2f { 4.0f, 282.0f });
    m_info->setShadow(jt::colors::Black, jt::Vector2f { 1.0f, 1.0f });
}

void SceneCircleTest::moveObstacle(Obstacle& obstacle, float const elapsed) const
{
    auto position = obstacle.shape->getPosition() + obstacle.velocity * elapsed;
    if (position.x < 0.0f || position.x > screenSize.x) {
        obstacle.velocity.x = -obstacle.velocity.x;
    }
    if (position.y < 0.0f || position.y > screenSize.y) {
        obstacle.velocity.y = -obstacle.velocity.y;
    }
    obstacle.shape->setPosition(position);
}

void SceneCircleTest::doUpdate(float const elapsed)
{
    m_player->setPosition(mouse()->getMousePositionWorld());
    m_player->update(elapsed);

    int numberOfHits { 0 };
    for (auto& obstacle : m_obstacles) {
        moveObstacle(obstacle, elapsed);
        obstacle.shape->update(elapsed);

        bool const isHit = jt::Collision::CircleTest(m_player, obstacle.shape);
        obstacle.shape->setColor(isHit ? hitColor : obstacleColor);
        if (isHit) {
            ++numberOfHits;
        }
    }

    m_info->setText("Move the mouse. Hits: " + std::to_string(numberOfHits) + " / "
        + std::to_string(m_obstacles.size()));
    m_info->update(elapsed);
}

void SceneCircleTest::doDraw() const
{
    for (auto const& obstacle : m_obstacles) {
        obstacle.shape->draw(renderTarget());
    }
    m_player->draw(renderTarget());
    m_info->draw(renderTarget());
}

std::string SceneCircleTest::getName() const { return "jt::Collision::CircleTest"; }
