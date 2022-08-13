
#ifndef JAMTEMPLATE_TEMPERATURE_MANAGER_HPP
#define JAMTEMPLATE_TEMPERATURE_MANAGER_HPP

#include <game_object.hpp>
#include <pathfinder/node_interface.hpp>
#include <shape.hpp>
#include <tilemap/info_rect.hpp>
#include <vector>

class TemperatureNode {
public:
    // TODO do use NodeInterface from Pathfinder
    TemperatureNode(std::shared_ptr<jt::pathfinder::NodeInterface> node);
    // TODO move to private
    float m_currentTemp { 0.0f };
    float m_throughputFactor { 0.9f };
    float m_inflow { 0.0f };
    float m_newTemp { 0.0f };

    void addNeighbour(std::weak_ptr<TemperatureNode> other);
    std::vector<std::weak_ptr<TemperatureNode>> const& getNeighbours();

    jt::Vector2f const& getPosition() const;
    jt::Vector2u const& getTilePosition() const;

private:
    jt::Vector2f m_position;
    jt::Vector2u m_tilePosition;
    std::vector<std::weak_ptr<TemperatureNode>> m_neighbours;
};

class TemperatureController {
public:
    explicit TemperatureController(std::vector<std::shared_ptr<TemperatureNode>> const& sensors,
        std::shared_ptr<TemperatureNode> node);

    void setInflow() const;

private:
    std::vector<std::shared_ptr<TemperatureNode>> m_sensors;
    std::shared_ptr<TemperatureNode> m_node;
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
    bool m_draw { true };
    std::vector<std::shared_ptr<TemperatureNode>> m_tempNodes;

    std::shared_ptr<jt::Shape> mutable m_shape;

    std::vector<std::shared_ptr<TemperatureController>> m_controllers;
    void createNodeConnections();
};

#endif // JAMTEMPLATE_TEMPERATURE_MANAGER_HPP
