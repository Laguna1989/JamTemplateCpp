#ifndef JAMTEMPLATE_LOG_TARGET_OSTREAM_HPP
#define JAMTEMPLATE_LOG_TARGET_OSTREAM_HPP

#include <log/log_target_interface.hpp>
#include <iostream>
#include <ostream>

namespace jt {
class LogTargetOstream : public LogTargetInterface {
public:
    explicit LogTargetOstream(std::ostream& stream = std::cout);
    void setLogLevel(LogLevel level) override;
    void log(LogEntry const& entry) override;

private:
    LogLevel m_logLevel { LogLevel::LogLevelDebug };
    std::ostream& m_stream;
};
} // namespace jt

#endif // JAMTEMPLATE_LOG_TARGET_OSTREAM_HPP
