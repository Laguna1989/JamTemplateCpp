#ifndef JAMTEMPLATE_CHARACTER_CONTROLLER_PLAYER_HPP
#define JAMTEMPLATE_CHARACTER_CONTROLLER_PLAYER_HPP

#include <input/keyboard/keyboard_interface.hpp>
#include <inventory/character/character_controller_interface.hpp>
#include <memory>

class CharacterControllerPlayer : public CharacterControllerInterface {
public:
    CharacterControllerPlayer(std::shared_ptr<jt::KeyboardInterface> keyboardInterface);
    void update(jt::Box2DObject& physObject) override;

private:
    std::shared_ptr<jt::KeyboardInterface> m_keyboard;
};

#endif // JAMTEMPLATE_CHARACTER_CONTROLLER_PLAYER_HPP
