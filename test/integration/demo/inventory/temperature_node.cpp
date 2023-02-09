#include "temperature_node.hpp"

TemperatureNode::TemperatureNode(std::shared_ptr<jt::pathfinder::NodeInterface> node)
{
    m_tilePosition = node->getTilePosition();
    m_position
        = jt::Vector2f { node->getTilePosition().x * 24.0f, node->getTilePosition().y * 24.0f };
}

jt::Vector2f const& TemperatureNode::getPosition() const { return m_position; }
jt::Vector2u const& TemperatureNode::getTilePosition() const { return m_tilePosition; }

void TemperatureNode::addNeighbour(std::weak_ptr<TemperatureNode> other)
{
    m_neighbours.push_back(other);
}

std::vector<std::weak_ptr<TemperatureNode>> const& TemperatureNode::getNeighbours()
{
    return m_neighbours;
}
float TemperatureNode::getCurrentTemperature() const { return m_currentTemp; }
void TemperatureNode::updateTemperatureFromInflow(float elapsed)
{
    float const m_maxTemp { 500.0f };
    m_currentTemp += m_inflow * elapsed;
    if (m_currentTemp < -m_maxTemp) {
        m_currentTemp = -m_maxTemp;
    }
    if (m_currentTemp > m_maxTemp) {
        m_currentTemp = m_maxTemp;
    }
}
void TemperatureNode::flipNewAndCurrentTemp() { m_currentTemp = m_newTemp; }
void TemperatureNode::setInflow(float inflow) { m_inflow = inflow; }
float TemperatureNode::getInflow() const { return m_inflow; }
void TemperatureNode::setNewTemp(float newTemp) { m_newTemp = newTemp; }
void TemperatureNode::setThroughputFactor(float factor) { m_throughputFactor = factor; }
float TemperatureNode::getThroughputFactor() const { return m_throughputFactor; }
