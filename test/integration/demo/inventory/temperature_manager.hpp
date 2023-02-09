
#ifndef JAMTEMPLATE_TEMPERATURE_MANAGER_HPP
#define JAMTEMPLATE_TEMPERATURE_MANAGER_HPP

#include <game_object.hpp>
#include <inventory/temperature_node.hpp>
#include <pathfinder/node_interface.hpp>
#include <shape.hpp>
#include <tilemap/info_rect.hpp>
#include <vector>

// controller for one heater and 0..N Sensors
class TemperatureController {
public:
    explicit TemperatureController(std::vector<std::shared_ptr<TemperatureNode>> const& sensors,
        std::shared_ptr<TemperatureNode> node);

    void setInflow() const;

private:
    std::vector<std::shared_ptr<TemperatureNode>> m_sensors;
    std::shared_ptr<TemperatureNode> m_node;
    // TODO make this configurable from tiled?
    float m_maxHeaterInflow { 50.0f };
};

class TemperatureManager : public jt::GameObject {
public:
    TemperatureManager(std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> nodes,
        std::vector<jt::tilemap::InfoRect> tempObjects);

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::shared_ptr<TemperatureNode> getNodeAt(jt::Vector2u const& pos);

private:
    bool m_draw { false };
    std::vector<std::shared_ptr<TemperatureNode>> m_tempNodes;

    std::shared_ptr<jt::Shape> mutable m_shape;

    std::vector<std::shared_ptr<TemperatureController>> m_controllers;
    void createNodeConnections();
};

#endif // JAMTEMPLATE_TEMPERATURE_MANAGER_HPP
