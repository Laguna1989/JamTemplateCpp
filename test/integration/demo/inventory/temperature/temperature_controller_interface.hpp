#ifndef JAMTEMPLATE_TEMPERATURE_CONTROLLER_INTERFACE_HPP
#define JAMTEMPLATE_TEMPERATURE_CONTROLLER_INTERFACE_HPP

#include <string>

class TemperatureControllerInterface {
public:
    virtual ~TemperatureControllerInterface() = default;
    virtual void setMaxHeaterInflow(float maxHeaterInflow) = 0;
    virtual float getMaxHeaterInflow() const = 0;
    virtual void setDesiredTemperature(float desiredTemperature) = 0;
    virtual float getDesiredTemperature() const = 0;
    virtual float getAverageSensorTemperature() const = 0;
    virtual std::string getName() const = 0;

    virtual void calculateInflow() const = 0;
};

#endif // JAMTEMPLATE_TEMPERATURE_CONTROLLER_INTERFACE_HPP
