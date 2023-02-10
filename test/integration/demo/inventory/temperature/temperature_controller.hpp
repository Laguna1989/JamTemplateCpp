
#ifndef JAMTEMPLATE_TEMPERATURE_CONTROLLER_HPP
#define JAMTEMPLATE_TEMPERATURE_CONTROLLER_HPP

#include <inventory/temperature/temperature_node.hpp>
#include <memory>
#include <string>
#include <vector>

// controller for one heater and 0..N Sensors
class TemperatureController {
public:
    explicit TemperatureController(std::vector<std::shared_ptr<TemperatureNode>> const& sensors,
        std::shared_ptr<TemperatureNode> node, std::string const& name);

    void calculateInflow() const;
    void setMaxHeaterInflow(float maxHeaterInflow);
    float getMaxHeaterInflow() const;

    void setDesiredTemperature(float desiredTemperature);
    float getDesiredTemperature() const;

    float getAverageSensorTemperature() const;
    std::string getName() const;

private:
    std::vector<std::shared_ptr<TemperatureNode>> m_sensors;
    std::shared_ptr<TemperatureNode> m_node;
    float m_maxHeaterInflow { 55.0f };
    float m_desiredTemperature { 0.0f };
    float mutable m_averageTemperature { 0.0f };
    std::string m_controllerName;
};

#endif // JAMTEMPLATE_TEMPERATURE_CONTROLLER_HPP
