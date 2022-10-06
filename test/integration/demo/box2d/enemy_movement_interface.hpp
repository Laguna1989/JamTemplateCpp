#ifndef JAMTEMPLATE_ENEMY_MOVEMENT_INTERFACE_HPP
#define JAMTEMPLATE_ENEMY_MOVEMENT_INTERFACE_HPP

#include <box2dwrapper/box2d_object.hpp>

class EnemyMovementInterface {
public:
    virtual ~EnemyMovementInterface() = default;
    virtual void update(float elapsed, std::shared_ptr<jt::Box2DObject> obj) = 0;
};

#endif // JAMTEMPLATE_ENEMY_MOVEMENT_INTERFACE_HPP
