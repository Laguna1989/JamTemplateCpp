#ifndef JAMTEMPLATE_ENEMY_MOVEMENT_HORIZONTAL_HPP
#define JAMTEMPLATE_ENEMY_MOVEMENT_HORIZONTAL_HPP

#include <box2d/enemy_movement_interface.hpp>

class EnemyMovementHorizontal : public EnemyMovementInterface {
public:
    EnemyMovementHorizontal(float minX, float maxX);
    void update(float elapsed, std::shared_ptr<jt::Box2DObject> obj) override;

private:
    float m_xMin { 0.0f };
    float m_xMax { 0.0f };
    bool m_movingRight { true };
};

#endif // JAMTEMPLATE_ENEMY_MOVEMENT_HORIZONTAL_HPP
