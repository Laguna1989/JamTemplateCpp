
#include "temperature_controller_master.hpp"
void TemperatureControllerMaster::setMaxHeaterInflow(float maxHeaterInflow)
{
    for (auto& controller : m_controllers) {
        auto c = controller.lock();
        c->setMaxHeaterInflow(maxHeaterInflow);
    }
}
float TemperatureControllerMaster::getMaxHeaterInflow() const
{
    float sum = 0.0f;
    for (auto& controller : m_controllers) {
        auto c = controller.lock();
        sum += c->getMaxHeaterInflow();
    }
    return sum / m_controllers.size();
}
void TemperatureControllerMaster::setDesiredTemperature(float desiredTemperature)
{
    for (auto& controller : m_controllers) {
        auto c = controller.lock();
        c->setDesiredTemperature(desiredTemperature);
    }
}
float TemperatureControllerMaster::getDesiredTemperature() const
{
    float sum = 0.0f;
    for (auto& controller : m_controllers) {
        auto c = controller.lock();
        sum += c->getDesiredTemperature();
    }
    return sum / m_controllers.size();
}
float TemperatureControllerMaster::getAverageSensorTemperature() const
{
    float sum = 0.0f;
    for (auto& controller : m_controllers) {
        auto c = controller.lock();
        sum += c->getAverageSensorTemperature();
    }
    return sum / m_controllers.size();
}
std::string TemperatureControllerMaster::getName() const { return "master"; }
void TemperatureControllerMaster::calculateInflow() const
{
    for (auto& controller : m_controllers) {
        auto c = controller.lock();
        c->calculateInflow();
    }
}
void TemperatureControllerMaster::addController(
    std::weak_ptr<TemperatureControllerInterface> controller)
{
    m_controllers.push_back(controller);
}
