#include "enemy_movement_vertical.hpp"

EnemyMovementVertical::EnemyMovementVertical(float minY, float maxY)
{
    m_yMin = minY;
    m_yMax = maxY;
}

void EnemyMovementVertical::update(float /*elapsed*/, std::shared_ptr<jt::Box2DObject> obj)
{
    auto const beeMovementSpeed = 30.0f;
    if (m_movingRight) {
        obj->setVelocity(jt::Vector2f { 0.0f, beeMovementSpeed });
        auto pos = obj->getPosition();
        if (pos.y >= m_yMax) {
            pos.y = m_yMax;
            m_movingRight = false;
        }
        obj->setPosition(pos);
    } else {
        obj->setVelocity(jt::Vector2f { 0.0f, -beeMovementSpeed });
        auto pos = obj->getPosition();
        if (pos.y <= m_yMin) {
            pos.y = m_yMin;
            m_movingRight = true;
        }
        obj->setPosition(pos);
    }
}
