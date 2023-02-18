
#ifndef JAMTEMPLATE_TEMPERATURE_CONTROLLER_HPP
#define JAMTEMPLATE_TEMPERATURE_CONTROLLER_HPP

#include <inventory/temperature/temperature_controller_interface.hpp>
#include <inventory/temperature/temperature_node.hpp>
#include <memory>
#include <vector>

// controller for one heater and 0..N Sensors
class TemperatureController : public TemperatureControllerInterface {
public:
    explicit TemperatureController(std::vector<std::shared_ptr<TemperatureNode>> const& sensors,
        std::shared_ptr<TemperatureNode> node, std::string const& name);

    void setMaxHeaterInflow(float maxHeaterInflow) override;
    float getMaxHeaterInflow() const override;

    void setDesiredTemperature(float desiredTemperature) override;
    float getDesiredTemperature() const override;

    float getAverageSensorTemperature() const override;
    std::string getName() const override;

    void calculateInflow() const override;

private:
    std::vector<std::shared_ptr<TemperatureNode>> m_sensors;
    std::shared_ptr<TemperatureNode> m_node;
    float m_maxHeaterInflow { 15.0f };
    float m_desiredTemperature { 0.0f };
    float mutable m_averageTemperature { 0.0f };
    std::string m_controllerName;
};

#endif // JAMTEMPLATE_TEMPERATURE_CONTROLLER_HPP
