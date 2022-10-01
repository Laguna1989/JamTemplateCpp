#ifndef JAMTEMPLATE_ENEMY_MOVEMENT_VERTICAL_HPP
#define JAMTEMPLATE_ENEMY_MOVEMENT_VERTICAL_HPP

#include <box2d/enemy_movement_interface.hpp>

class EnemyMovementVertical : public EnemyMovementInterface {
public:
    EnemyMovementVertical(float minY, float maxY);
    void update(float elapsed, std::shared_ptr<jt::Box2DObject> obj) override;

private:
    float m_yMin { 0.0f };
    float m_yMax { 0.0f };
    bool m_movingRight { true };
};

#endif // JAMTEMPLATE_ENEMY_MOVEMENT_VERTICAL_HPP
