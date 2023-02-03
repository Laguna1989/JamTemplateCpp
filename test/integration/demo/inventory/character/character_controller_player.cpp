#include "character_controller_player.hpp"

CharacterControllerPlayer::CharacterControllerPlayer(
    std::shared_ptr<jt::KeyboardInterface> keyboardInterface)
{
    m_keyboard = keyboardInterface;
}

void CharacterControllerPlayer::update(jt::Box2DObject& physObject)
{
    jt::Vector2f newVelocity { 0.0f, 0.0f };
    float const speed = 85.0f;
    if (m_keyboard->pressed(jt::KeyCode::D)) {
        newVelocity += jt::Vector2f { speed, 0.0f };
    }
    if (m_keyboard->pressed(jt::KeyCode::A)) {
        newVelocity += jt::Vector2f { -speed, 0.0f };
    }

    if (m_keyboard->pressed(jt::KeyCode::W)) {
        newVelocity += jt::Vector2f { 0.0f, -speed };
    }
    if (m_keyboard->pressed(jt::KeyCode::S)) {
        newVelocity += jt::Vector2f { 0.0f, speed };
    }

    physObject.setVelocity(newVelocity);
}
