#include "temperature_manager.hpp"
#include <game_interface.hpp>
#include <inventory/temperature/temperature_controller.hpp>
#include <linterp.hpp>
#include <math_helper.hpp>
#include <strutils.hpp>
#include <algorithm>
#include <iostream>

TemperatureManager::TemperatureManager(
    std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> nodes,
    std::vector<jt::tilemap::InfoRect> tempObjects)
{
    // create temperatureNodes based on pathfinder nodes
    for (auto const& node : nodes) {
        auto temperatureNode = std::make_shared<TemperatureNode>(node);
        if (node->getBlocked()) {
            temperatureNode->setThroughputFactor(0.0f);
        }
        m_tempNodes.push_back(temperatureNode);
    }
    m_masterController = std::make_shared<TemperatureControllerMaster>();

    createNodeConnections();
    std::map<std::string, std::shared_ptr<TemperatureNode>> sensors;
    for (auto const& obj : tempObjects) {
        auto tilePos = jt::Vector2u { static_cast<unsigned int>(obj.position.x / 24.0f),
            static_cast<unsigned int>(obj.position.y / 24.0f) };

        if (obj.properties.strings.at("type") == "const") {
            float inflowValue = obj.properties.floats.at("value");
            getNodeAt(tilePos)->setInflow(inflowValue);
            std::cout << "spawn const heater (" << inflowValue << ")\n";
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

            auto controller = std::make_shared<TemperatureController>(
                currentSensors, getNodeAt(tilePos), obj.name);
            m_controllers.emplace_back(controller);
            m_masterController->addController(controller);
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
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::V)) {
        std::cout << "changed drawmode\n";
        m_draw = !m_draw;
    }
    m_shape->update(elapsed);

    for (auto const& c : m_controllers) {
        c->calculateInflow();
    }

    for (auto const& n : m_tempNodes) {
        n->updateTemperatureFromInflow(elapsed);
    }

    for (auto const& n : m_tempNodes) {
        float newTemperature = n->getCurrentTemperature();
        // diffusion
        for (auto ot : n->getNeighbours()) {
            auto other = ot.lock();
            if (!other) {
                continue;
            }

            auto const diff = other->getCurrentTemperature() - n->getCurrentTemperature();
            auto const throughPutFactor = n->getThroughputFactor() * other->getThroughputFactor();
            newTemperature += diff * elapsed * throughPutFactor * 2.5f;
        }
        n->setNewTemp(newTemperature);
    }

    for (auto const& n : m_tempNodes) {
        n->flipNewAndCurrentTemp();
    }
}

void TemperatureManager::doDraw() const
{
    if (!m_draw) {
        return;
    }
    for (auto const& n : m_tempNodes) {

        m_shape->setPosition(n->getPosition());
        constexpr auto maxTempDisplayValue = 25.0f;
        // between 0 and 1
        float const t
            = std::clamp(n->getCurrentTemperature(), -maxTempDisplayValue, maxTempDisplayValue)
                / (2 * maxTempDisplayValue)
            + 0.5f;

        std::uint8_t const r = static_cast<std::uint8_t>(std::lerp(5.0f, 255.0f, t));
        std::uint8_t const g = static_cast<std::uint8_t>(std::lerp(150.0f, 150.0f, t));
        std::uint8_t const b = static_cast<std::uint8_t>(std::lerp(255.0f, 5.0f, t));
        std::uint8_t const a = static_cast<std::uint8_t>(150 + abs(t - 0.5f) * 2 * 50);

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

std::weak_ptr<TemperatureControllerInterface> TemperatureManager::getControllerByName(
    std::string const& name)
{
    if (name == "master") {
        return m_masterController;
    }
    for (auto const& c : m_controllers) {
        if (c->getName() == name) {
            return c;
        }
    }
    return std::weak_ptr<TemperatureControllerInterface>();
}
