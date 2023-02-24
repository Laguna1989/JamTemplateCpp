
#ifndef JAMTEMPLATE_TEMPERATURE_MANAGER_HPP
#define JAMTEMPLATE_TEMPERATURE_MANAGER_HPP

#include <game_object.hpp>
#include <inventory/temperature/temperature_controller_interface.hpp>
#include <inventory/temperature/temperature_controller_master.hpp>
#include <inventory/temperature/temperature_node.hpp>
#include <pathfinder/node_interface.hpp>
#include <shape.hpp>
#include <tilemap/info_rect.hpp>
#include <vector>

class TemperatureManager : public jt::GameObject {
public:
    TemperatureManager(std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> nodes,
        std::vector<jt::tilemap::InfoRect> tempObjects);

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::shared_ptr<TemperatureNode> getNodeAt(jt::Vector2u const& pos);

    std::weak_ptr<TemperatureControllerInterface> getControllerByName(std::string const& name);

private:
    bool m_draw { false };
    std::vector<std::shared_ptr<TemperatureNode>> m_tempNodes;

    std::shared_ptr<jt::Shape> mutable m_shape;

    std::vector<std::shared_ptr<TemperatureControllerInterface>> m_controllers;
    std::shared_ptr<TemperatureControllerMaster> m_masterController;
    void createNodeConnections();
};

#endif // JAMTEMPLATE_TEMPERATURE_MANAGER_HPP
