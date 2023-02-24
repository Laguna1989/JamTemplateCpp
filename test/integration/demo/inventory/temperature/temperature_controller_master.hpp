#ifndef JAMTEMPLATE_TEMPERATURE_CONTROLLER_MASTER_HPP
#define JAMTEMPLATE_TEMPERATURE_CONTROLLER_MASTER_HPP

#include <inventory/temperature/temperature_controller_interface.hpp>
#include <memory>
#include <vector>

class TemperatureControllerMaster : public TemperatureControllerInterface {
public:
    void setMaxHeaterInflow(float maxHeaterInflow) override;
    float getMaxHeaterInflow() const override;
    void setDesiredTemperature(float desiredTemperature) override;
    float getDesiredTemperature() const override;
    float getAverageSensorTemperature() const override;
    std::string getName() const override;
    void calculateInflow() const override;
    void addController(std::weak_ptr<TemperatureControllerInterface> controller);

private:
    std::vector<std::weak_ptr<TemperatureControllerInterface>> m_controllers;
};

#endif // JAMTEMPLATE_TEMPERATURE_CONTROLLER_MASTER_HPP
