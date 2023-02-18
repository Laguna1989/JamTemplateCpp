#include "object_controller.hpp"
#include <game_interface.hpp>
#include <math_helper.hpp>
#include <system_helper.hpp>
#include "imgui.h"

ObjectController::ObjectController(jt::Vector2f const& pos)
    : m_pos { pos }
{
}

void ObjectController::doCreate()
{
    m_sprite = std::make_shared<jt::Sprite>(
        "assets/test/integration/demo/door.png", jt::Recti { 96, 0, 24, 24 }, textureManager());
    m_sprite->setPosition(m_pos);
}
void ObjectController::doUpdate(float const elapsed)
{
    m_sprite->update(elapsed);
    jt::Vector2f const dif { m_playerPos.x - m_pos.x, m_playerPos.y - m_pos.y };
    m_draw = (jt::MathHelper::lengthSquared(dif) < 24 * 24);
}
void ObjectController::doDraw() const
{
    m_sprite->draw(renderTarget());

    if (m_draw) {
        ImGui::Begin("Controller");
        for (auto const& door : m_doors) {
            auto d = door.lock();
            auto const n = d->getDoorName();
            ImGui::Text("Door: %s", n.c_str());
            if (ImGui::Button(n.c_str())) {
                d->toggleDoor();
            }
            ImGui::Separator();
        }
        ImGui::Separator();
        for (auto const& heater : m_heaters) {
            auto h = heater.lock();
            ImGui::Text("Temperature Controller %s", h->getName().c_str());
            ImGui::Text("avg temp: %.1f", h->getAverageSensorTemperature());

            float maxInflow = h->getMaxHeaterInflow();
            std::string const labelName1 = "max Flow##" + h->getName();

            ImGui::SliderFloat(labelName1.c_str(), &maxInflow, 0.0f, 30.0f, "%.1f", 0);
            h->setMaxHeaterInflow(maxInflow);

            float desiredTemp = h->getDesiredTemperature();
            std::string const labelName2 = "desired Temp##" + h->getName();
            ImGui::SliderFloat(labelName2.c_str(), &desiredTemp, -30.0f, 30.0f, "%.1f", 0);
            h->setDesiredTemperature(desiredTemp);
            ImGui::Separator();
        }
        ImGui::End();
    }
}
void ObjectController::addDoor(std::weak_ptr<ObjectDoor> door)
{
    if (jt::SystemHelper::is_uninitialized_weak_ptr(door)) {
        getGame()->logger().warning(
            "warning, object controller wants to control non existing door");
        return;
    }
    m_doors.push_back(door);
}
void ObjectController::setPlayerPosition(jt::Vector2f const& pos) { m_playerPos = pos; }
void ObjectController::addHeater(std::weak_ptr<TemperatureControllerInterface> heater)
{

    if (jt::SystemHelper::is_uninitialized_weak_ptr(heater)) {
        getGame()->logger().warning(
            "warning, object controller wants to control non existing heater");
        return;
    }
    m_heaters.push_back(heater);
}
