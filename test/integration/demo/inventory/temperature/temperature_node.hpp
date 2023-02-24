
#ifndef JAMTEMPLATE_TEMPERATURE_NODE_HPP
#define JAMTEMPLATE_TEMPERATURE_NODE_HPP

#include <pathfinder/node_interface.hpp>
#include <memory>
#include <vector>

class TemperatureNode {
public:
    TemperatureNode(std::shared_ptr<jt::pathfinder::NodeInterface> node);

    void addNeighbour(std::weak_ptr<TemperatureNode> other);
    std::vector<std::weak_ptr<TemperatureNode>> const& getNeighbours();

    jt::Vector2f const& getPosition() const;
    jt::Vector2u const& getTilePosition() const;

    float getCurrentTemperature() const;
    void updateTemperatureFromInflow(float elapsed);
    void flipNewAndCurrentTemp();

    void setInflow(float inflow);
    float getInflow() const;
    void setNewTemp(float newTemp);

    void setThroughputFactor(float factor);
    float getThroughputFactor() const;

private:
    jt::Vector2f m_position;
    jt::Vector2u m_tilePosition;
    std::vector<std::weak_ptr<TemperatureNode>> m_neighbours;

    float m_currentTemp { 0.0f };
    float m_inflow { 0.0f };
    float m_newTemp { 0.0f };
    float m_throughputFactor { 0.95f };
};

#endif // JAMTEMPLATE_TEMPERATURE_NODE_HPP
