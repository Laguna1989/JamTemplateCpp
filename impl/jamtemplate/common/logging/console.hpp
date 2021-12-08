#ifndef GUARD_JAMTEMPLATE_CONSOLE_HPP
#define GUARD_JAMTEMPLATE_CONSOLE_HPP

#include "game_object.hpp"
#include "log_entry.hpp"
#include "logger_interface.hpp"
#include <memory>
#include <string>
#include <vector>

namespace jt {

class Console : public jt::GameObject {
public:
    Console(std::shared_ptr<jt::LoggerInterface> target);

    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    // TODO Add callbacks for commands
private:
    std::shared_ptr<LoggerInterface> m_logger;

    mutable bool m_showConsole { false };
    mutable std::vector<char> m_inputBufferFilter;
    mutable std::vector<char> m_inputBufferAction;
    mutable std::string m_lastCommand { "" };
    mutable bool m_drawLevel { true };
    mutable bool m_drawTag { true };
    mutable bool m_drawTime { false };

    void renderOneLogEntry(jt::LogEntry const& entry) const;
    void storeInputInCommand() const;
    void clearInput() const;
    void storeActionInCommand() const;
    void handleCommand() const;
    void drawFilter() const;
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_CONSOLE_HPP
