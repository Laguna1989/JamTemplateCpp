#ifndef GUARD_JAMTEMPLATE_LOG_HPP
#define GUARD_JAMTEMPLATE_LOG_HPP

#include "log_entry.hpp"
#include "log_interface.hpp"
#include <vector>

namespace jt {
class Log : public jt::LogInterface {
public:
    // TODO set log level to avoid spamming
    // TODO add action command
    // TODO add forward to cout cerr, e.g. via decorator?
    void debug(std::string const& string) override;
    void verbose(std::string const& string) override;
    void error(std::string const& string) override;
    void clear() override;

    std::vector<jt::LogEntry> getAllLogs() override;

private:
    std::vector<jt::LogEntry> m_allLogs;
};
} // namespace jt

#endif // MYAWESOMEGAME_LOG_HPP
