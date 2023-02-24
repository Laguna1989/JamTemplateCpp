#ifndef JAMTEMPLATE_CHARACTER_CONTROLLER_WALK_HPP
#define JAMTEMPLATE_CHARACTER_CONTROLLER_WALK_HPP

#include <inventory/character/character_controller_interface.hpp>

class CharacterControllerWalk : public CharacterControllerInterface {
public:
    void update(jt::Box2DObject& physObject) override;
    bool m_walk_right { true };
};

#endif // JAMTEMPLATE_CHARACTER_CONTROLLER_WALK_HPP
