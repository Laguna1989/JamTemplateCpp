#ifndef MYAWESOMEGAME_INPUT_COMPONENT_INTERFACE_HPP
#define MYAWESOMEGAME_INPUT_COMPONENT_INTERFACE_HPP

#include <player/input/input_target_interface.hpp>

class InputComponentInterface {
public:
    virtual ~InputComponentInterface() = default;

    virtual void updateMovement(InputTargetInterface& target) = 0;
};

#endif // MYAWESOMEGAME_INPUT_COMPONENT_INTERFACE_HPP
