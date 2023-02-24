#include "enemy_movement_horizontal.hpp"

EnemyMovementHorizontal::EnemyMovementHorizontal(float minX, float maxX)
{
    m_xMin = minX;
    m_xMax = maxX;
    if (m_xMin > m_xMax) {
        std::swap(m_xMin, m_xMax);
    }
}

void EnemyMovementHorizontal::update(float /*elapsed*/, std::shared_ptr<jt::Box2DObject> obj)
{
    auto const beeMovementSpeed = 30.0f;
    if (m_movingRight) {
        obj->setVelocity(jt::Vector2f { beeMovementSpeed, 0.0f });
        auto pos = obj->getPosition();
        if (pos.x >= m_xMax) {
            pos.x = m_xMax;
            m_movingRight = false;
        }
        obj->setPosition(pos);
    } else {
        obj->setVelocity(jt::Vector2f { -beeMovementSpeed, 0.0f });
        auto pos = obj->getPosition();
        if (pos.x <= m_xMin) {
            pos.x = m_xMin;
            m_movingRight = true;
        }
        obj->setPosition(pos);
    }
}
