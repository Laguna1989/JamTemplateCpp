
#ifndef JAMTEMPLATE_OBJECT_DOOR_HPP
#define JAMTEMPLATE_OBJECT_DOOR_HPP

#include "temperature_node.hpp"
#include <animation.hpp>
#include <game_object.hpp>
#include <memory>

class ObjectDoor : public jt::GameObject {
public:
    ObjectDoor(std::weak_ptr<TemperatureNode> node);
    bool m_closed { false };
    float m_inflowClosed;
    float m_inflowOpen;
    std::string m_name;

    void toggleDoor();

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

private:
    std::weak_ptr<TemperatureNode> m_tempNode;
    std::shared_ptr<jt::Animation> m_anim;
};

#endif // JAMTEMPLATE_OBJECT_DOOR_HPP
