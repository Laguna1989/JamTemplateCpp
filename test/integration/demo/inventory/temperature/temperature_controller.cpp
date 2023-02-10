#include "temperature_controller.hpp"

TemperatureController::TemperatureController(
    std::vector<std::shared_ptr<TemperatureNode>> const& sensors,
    std::shared_ptr<TemperatureNode> node, std::string const& name)
{
    m_sensors = sensors;
    m_node = node;
    m_controllerName = name;
}

void TemperatureController::calculateInflow() const
{
    float temperatureSumOfAllSensors = 0.0f;
    for (auto const& n : m_sensors) {
        temperatureSumOfAllSensors += n->getCurrentTemperature();
    }

    m_averageTemperature = temperatureSumOfAllSensors / m_sensors.size();

    float desiredInflow = (m_desiredTemperature - m_averageTemperature) * 20.0f;
    if (desiredInflow < -m_maxHeaterInflow) {
        desiredInflow = -m_maxHeaterInflow;
    } else if (desiredInflow > m_maxHeaterInflow) {
        desiredInflow = m_maxHeaterInflow;
    }
    m_node->setInflow(desiredInflow);
}
void TemperatureController::setMaxHeaterInflow(float maxHeaterInflow)
{
    m_maxHeaterInflow = maxHeaterInflow;
}
float TemperatureController::getMaxHeaterInflow() const { return m_maxHeaterInflow; }
void TemperatureController::setDesiredTemperature(float desiredTemperature)
{
    m_desiredTemperature = desiredTemperature;
}
float TemperatureController::getDesiredTemperature() const { return m_desiredTemperature; }
float TemperatureController::getAverageSensorTemperature() const { return m_averageTemperature; }
std::string TemperatureController::getName() const { return m_controllerName; }
