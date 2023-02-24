
#include "character_controller_walk.hpp"

// 13,4 - 21,4
void CharacterControllerWalk::update(jt::Box2DObject& physObject)
{
    jt::Vector2f newVelocity { 0.0f, 0.0f };
    float const speed = 65.0f;
    auto const pos = physObject.getPosition();
    if (m_walk_right) {
        newVelocity += jt::Vector2f { speed, 0.0f };
        if (pos.x > 21.0f * 24) {
            m_walk_right = false;
            physObject.setPosition(jt::Vector2f { 21.0 * 24, pos.y });
            newVelocity = { 0.0f, 0.0f };
        }
    } else {
        newVelocity += jt::Vector2f { -speed, 0.0f };
        if (pos.x < 13.0f * 24) {
            m_walk_right = true;
            physObject.setPosition(jt::Vector2f { 13.0f * 24, pos.y });
            newVelocity = { 0.0f, 0.0f };
        }
    }

    physObject.setVelocity(newVelocity);
}
