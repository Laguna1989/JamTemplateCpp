
#ifndef JAMTEMPLATE_OBJECT_DOOR_HPP
#define JAMTEMPLATE_OBJECT_DOOR_HPP

#include "animation.hpp"
#include "game_object.hpp"
#include "inventory/temperature/temperature_node.hpp"
#include <memory>

class ObjectDoor : public jt::GameObject {
public:
    ObjectDoor(std::weak_ptr<TemperatureNode> node);
    bool m_closed { false };
    float m_inflowClosed;
    float m_inflowOpen;

    void toggleDoor();
    bool getIsOpen() const;

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::string getDoorName() const;
    void setDoorName(std::string const& name);

private:
    std::weak_ptr<TemperatureNode> m_tempNode;
    std::shared_ptr<jt::Animation> m_anim;
    std::string m_name;
};

#endif // JAMTEMPLATE_OBJECT_DOOR_HPP
