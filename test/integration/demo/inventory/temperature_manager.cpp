#include "temperature_manager.hpp"
#include <game_interface.hpp>
#include <linterp.hpp>
#include <math_helper.hpp>
#include <strutils.hpp>
#include <iostream>

TemperatureManager::TemperatureManager(
    std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> nodes,
    std::vector<jt::tilemap::InfoRect> tempObjects)
{
    for (auto const& node : nodes) {

        auto temperatureNode = std::make_shared<TemperatureNode>(node);
        if (node->getBlocked()) {
            temperatureNode->m_throughputFactor = 0.0f;
        }
        m_tempNodes.push_back(temperatureNode);
    }

    createNodeConnections();
    std::map<std::string, std::shared_ptr<TemperatureNode>> sensors;
    for (auto const& obj : tempObjects) {
        auto tilePos = jt::Vector2u { static_cast<unsigned int>(obj.position.x / 24.0f),
            static_cast<unsigned int>(obj.position.y / 24.0f) };

        if (obj.properties.strings.at("type") == "const") {
            getNodeAt(tilePos)->m_inflow = obj.properties.floats.at("value");
            std::cout << "spawn const heater\n";
        } else if (obj.properties.strings.at("type") == "sensor") {
            sensors[obj.name] = getNodeAt(tilePos);
        }
    }
    for (auto const& obj : tempObjects) {
        auto tilePos = jt::Vector2u { static_cast<unsigned int>(obj.position.x / 24.0f),
            static_cast<unsigned int>(obj.position.y / 24.0f) };
        if (obj.properties.strings.at("type") == "controlled") {
            std::vector<std::shared_ptr<TemperatureNode>> currentSensors;
            auto sensorString = obj.properties.strings.at("sensors");
            auto sensorsVector = strutil::split(sensorString, ",");
            for (auto& s : sensorsVector) {
                strutil::trim(s);
                currentSensors.push_back(sensors[s]);
            }

            m_controllers.emplace_back(
                std::make_shared<TemperatureController>(currentSensors, getNodeAt(tilePos)));
        }
    }
}
void TemperatureManager::createNodeConnections()
{
    for (auto& t : m_tempNodes) {
        auto const currentPos = t->getTilePosition();
        for (int i = -1; i != 2; ++i) {
            for (int j = -1; j != 2; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }
                auto const ox = static_cast<int>(currentPos.x) + i;
                auto const oy = static_cast<int>(currentPos.y) + j;
                auto const ot = getNodeAt(
                    jt::Vector2u { static_cast<unsigned int>(ox), static_cast<unsigned int>(oy) });
                if (ot) {
                    t->addNeighbour(ot);
                }
            }
        }
    }
}

void TemperatureManager::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeRect(jt::Vector2f { 24.0f, 24.0f }, textureManager());
}
void TemperatureManager::doUpdate(float const elapsed)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Num1)) {
        m_draw = !m_draw;
    }
    m_shape->update(elapsed);

    for (auto const& c : m_controllers) {
        c->setInflow();
    }

    for (auto const& n : m_tempNodes) {
        n->m_currentTemp += n->m_inflow * elapsed;
        n->m_newTemp = n->m_currentTemp;
        // diffusion
        for (auto ot : n->getNeighbours()) {
            auto other = ot.lock();
            if (!other) {
                continue;
            }

            auto const diff = other->m_currentTemp - n->m_currentTemp;
            auto tpf = n->m_throughputFactor * other->m_throughputFactor;
            n->m_newTemp += diff * elapsed * tpf;
        }
    }

    for (auto const& n : m_tempNodes) {
        n->m_currentTemp = n->m_newTemp;
    }
}
void TemperatureManager::doDraw() const
{
    if (!m_draw) {
        return;
    }
    for (auto const& n : m_tempNodes) {

        m_shape->setPosition(n->getPosition());

        // between 0 and 1
        float const t = jt::MathHelper::clamp(n->m_currentTemp, -50.0f, 50.0f) / 100.0f + 0.5f;

        std::uint8_t const r = static_cast<std::uint8_t>(jt::Lerp::linear(50.0f, 250.0f, t));
        std::uint8_t const g = static_cast<std::uint8_t>(jt::Lerp::linear(150.0f, 150.0f, t));
        std::uint8_t const b = static_cast<std::uint8_t>(jt::Lerp::linear(250.0f, 50.0f, t));
        std::uint8_t const a = 200u;
        m_shape->setColor(jt::Color { r, g, b, a });

        m_shape->update(0.1f);
        m_shape->draw(renderTarget());
    }
}
std::shared_ptr<TemperatureNode> TemperatureManager::getNodeAt(jt::Vector2u const& pos)
{
    for (auto const& n : m_tempNodes) {
        if (n->getTilePosition() == pos)
            return n;
    }
    return nullptr;
}

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
TemperatureController::TemperatureController(
    std::vector<std::shared_ptr<TemperatureNode>> const& sensors,
    std::shared_ptr<TemperatureNode> node)
{
    m_sensors = sensors;
    m_node = node;
}

void TemperatureController::setInflow() const
{
    float sum = 0.0f;
    for (auto const& n : m_sensors) {
        sum += n->m_currentTemp;
    }

    float const averageTemperature = sum / m_sensors.size();
    m_node->m_inflow = -averageTemperature * 20.0f;
}
