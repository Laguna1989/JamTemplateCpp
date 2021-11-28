#ifndef GUARD_JAMTEMPLATE_CONTROL_COMMAND_MOVECAM_HPP
#define GUARD_JAMTEMPLATE_CONTROL_COMMAND_MOVECAM_HPP

#include "control_command_interface.hpp"
#include "vector.hpp"

class ControlCommandMoveCam : public jt::ControlCommandInterface {
public:
    explicit ControlCommandMoveCam(jt::Vector2 scrollDirection);
    void execute(float elapsed) override { }
};

#endif // MYAWESOMEGAME_CONTROL_COMMAND_MOVECAM_HPP
