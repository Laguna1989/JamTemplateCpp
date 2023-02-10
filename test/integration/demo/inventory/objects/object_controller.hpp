
#ifndef JAMTEMPLATE_OBJECT_CONTROLLER_HPP
#define JAMTEMPLATE_OBJECT_CONTROLLER_HPP

#include "sprite.hpp"
#include <game_object.hpp>
#include <inventory/objects/object_door.hpp>
#include <inventory/temperature/temperature_controller.hpp>
#include <vector.hpp>
#include <memory>
#include <vector>

class ObjectController : public jt::GameObject {
public:
    ObjectController(jt::Vector2f const& pos);

    void addDoor(std::weak_ptr<ObjectDoor> door);
    void addHeater(std::weak_ptr<TemperatureController> heater);
    void setPlayerPosition(jt::Vector2f const& pos);

private:
    bool m_draw { false };
    jt::Vector2f m_pos;
    jt::Vector2f m_playerPos;
    std::shared_ptr<jt::Sprite> m_sprite;
    std::vector<std::weak_ptr<ObjectDoor>> m_doors;
    std::vector<std::weak_ptr<TemperatureController>> m_heaters;

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // JAMTEMPLATE_OBJECT_CONTROLLER_HPP
