
#ifndef JAMTEMPLATE_OBJECT_DOOR_HPP
#define JAMTEMPLATE_OBJECT_DOOR_HPP

#include "inventory/temperature/temperature_node.hpp"
#include <animation.hpp>
#include <box2dwrapper/box2d_object.hpp>
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_object.hpp>
#include <memory>

class ObjectDoor : public jt::GameObject {
public:
    ObjectDoor(std::weak_ptr<TemperatureNode> node, std::shared_ptr<jt::Box2DWorldInterface> world);
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
    std::shared_ptr<jt::Animation> m_anim { nullptr };
    std::string m_name { "" };
    std::shared_ptr<jt::Box2DObject> m_physicsObject { nullptr };
};

#endif // JAMTEMPLATE_OBJECT_DOOR_HPP
