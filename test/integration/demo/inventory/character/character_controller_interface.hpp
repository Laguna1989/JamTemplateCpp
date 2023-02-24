
#ifndef JAMTEMPLATE_CHARACTER_CONTROLLER_INTERFACE_HPP
#define JAMTEMPLATE_CHARACTER_CONTROLLER_INTERFACE_HPP

#include <box2dwrapper/box2d_object.hpp>
class CharacterControllerInterface {
public:
    virtual ~CharacterControllerInterface() = default;
    virtual void update(jt::Box2DObject& physObject) = 0;
};

#endif // JAMTEMPLATE_CHARACTER_CONTROLLER_INTERFACE_HPP
