#include "control_command_move_b_2_body.hpp"
#include <iostream>

ControlCommandMoveB2Body::ControlCommandMoveB2Body(
    jt::Vector2f scrollDirection, std::weak_ptr<jt::Box2DObject> obj)
    : m_vec { scrollDirection }
    , m_obj { obj }
{
}

void ControlCommandMoveB2Body::doExecute(float /*elapsed*/)
{
    auto obj = m_obj.lock();
    if (obj) {
        std::cout << "control move command b2body\n";
        obj->setVelocity(m_vec);
    }
}
