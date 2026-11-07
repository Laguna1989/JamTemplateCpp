#pragma once

#include <input/control_commands/control_command_interface.hpp>

namespace jt {

class ControlCommandNull : public ControlCommandInterface {
public:
    void execute(float elapsed) override;
    void reset() override;
};
} // namespace jt
