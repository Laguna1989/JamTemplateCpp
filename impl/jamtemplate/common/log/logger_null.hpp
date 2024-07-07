#ifndef JAMTEMPLATE_LOGGER_NULL_HPP
#define JAMTEMPLATE_LOGGER_NULL_HPP

#include <log/logger_interface.hpp>

namespace jt {

class LogTargetInterface;

namespace null_objects {

class LoggerNull : public jt::LoggerInterface {
public:
    void action(
        std::string const& string) override;
    void fatal(std::string const& string, std::vector<std::string> const& tags = {}) override;
    void error(std::string const& string, std::vector<std::string> const& tags = {}) override;
    void warning(std::string const& string, std::vector<std::string> const& tags = {}) override;
    void info(std::string const& string, std::vector<std::string> const& tags = {}) override;
    void debug(std::string const& string, std::vector<std::string> const& tags = {}) override;
    void verbose(std::string const& string, std::vector<std::string> const& tags = {}) override;
    void addLogTarget(std::shared_ptr<LogTargetInterface> target) override;
    void setLogLevel(LogLevel level) override;
};
} // namespace null_objects
} // namespace jt

#endif // JAMTEMPLATE_LOGGER_NULL_HPP
