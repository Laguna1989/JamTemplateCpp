#ifndef GAME_PLAYER_INPUT_COMPONENT_HPP
#define GAME_PLAYER_INPUT_COMPONENT_HPP

#include <input/input_manager_interface.hpp>
#include <player/input/input_component_interface.hpp>
#include <memory>

class InputComponentImpl : public InputComponentInterface {
public:
    explicit InputComponentImpl(std::shared_ptr<jt::KeyboardInterface> keyboardInterface);

    void updateMovement(InputTargetInterface& player) override;

private:
    std::shared_ptr<jt::KeyboardInterface> m_keyboard { nullptr };
};

#endif // GAME_PLAYER_INPUT_COMPONENT_HPP
