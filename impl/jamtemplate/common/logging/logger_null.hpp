#ifndef MYAWESOMEGAME_LOGGER_NULL_HPP
#define MYAWESOMEGAME_LOGGER_NULL_HPP

#include "logging/logger_interface.hpp"

namespace jt {
namespace null_objects {

class LoggerNull : public jt::LoggerInterface {
public:
    void action(std::string const& string) override;
    void fatal(std::string const& string, std::vector<std::string> tags = {}) override;
    void error(std::string const& string, std::vector<std::string> tags = {}) override;
    void warning(std::string const& string, std::vector<std::string> tags = {}) override;
    void info(std::string const& string, std::vector<std::string> tags = {}) override;
    void debug(std::string const& string, std::vector<std::string> tags = {}) override;
    void verbose(std::string const& string, std::vector<std::string> tags = {}) override;
    void addLogTarget(std::shared_ptr<LogTargetInterface> target) override;
    std::vector<jt::LogEntry> const& getHistory() override;
    void clear() override;
    void setLogLevel(LogLevel level) override;

private:
    std::vector<jt::LogEntry> m_history;
};
} // namespace null_objects
} // namespace jt

#endif // MYAWESOMEGAME_LOGGER_NULL_HPP
