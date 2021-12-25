#ifndef GUARD_JAMTEMPLATE_CONTROL_COMMAND_COMPOSITE_HPP
#define GUARD_JAMTEMPLATE_CONTROL_COMMAND_COMPOSITE_HPP

#include "control_command_interface.hpp"
#include <memory>
#include <vector>

namespace jt {

class ControlCommandComposite : public jt::ControlCommandInterface {
public:
    ControlCommandComposite(std::vector<std::shared_ptr<jt::ControlCommandInterface>> const&);
    void execute(float elapsed) override;
    void reset() override;

private:
    std::vector<std::shared_ptr<jt::ControlCommandInterface>> m_commands;
};

} // namespace jt

#endif // MYAWESOMEGAME_CONTROL_COMMAND_COMPOSITE_HPP
