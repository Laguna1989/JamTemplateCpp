#ifndef MYAWESOMEGAME_CONTROL_COMMAND_MOVE_B_2_BODY_HPP
#define MYAWESOMEGAME_CONTROL_COMMAND_MOVE_B_2_BODY_HPP

#include "box2dwrapper/box2d_object.hpp"
#include "input/control_command_once.hpp"

class ControlCommandMoveB2Body : public jt::ControlCommandOnce {
public:
    ControlCommandMoveB2Body(jt::Vector2f scrollDirection, std::weak_ptr<jt::Box2DObject> obj);

private:
    void doExecute(float elapsed) override;

private:
    jt::Vector2f m_vec;
    std::weak_ptr<jt::Box2DObject> m_obj;
};

#endif // MYAWESOMEGAME_CONTROL_COMMAND_MOVE_B_2_BODY_HPP
