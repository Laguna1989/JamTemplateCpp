#ifndef GUARD_JAMTEMPLATE_CONSOLE_HPP
#define GUARD_JAMTEMPLATE_CONSOLE_HPP

#include "game_object.hpp"
#include "log_entry.hpp"
#include "log_interface.hpp"
#include <string>
#include <vector>

namespace jt {

class Console : public jt::GameObject {
public:
    Console(std::shared_ptr<jt::LogInterface> log);

    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    // TODO Add Textfield for entering commands
    // TODO Add callbacks for commands
    // TODO Print with or without Time
private:
    std::shared_ptr<LogInterface> m_log;
    void renderOneLogEntry(jt::LogEntry const& entry) const;
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_CONSOLE_HPP
