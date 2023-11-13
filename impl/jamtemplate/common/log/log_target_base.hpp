#ifndef JAMTEMPLATE_LOG_TARGET_BASE_HPP
#define JAMTEMPLATE_LOG_TARGET_BASE_HPP

#include <log/log_target_interface.hpp>

namespace jt {

class LogTargetBase : public jt::LogTargetInterface {
public:
    virtual ~LogTargetBase() = default;

    void log(LogEntry const& entry) override;

    void setLogLevel(LogLevel level) override;
    LogLevel getLogLevel() const;

private:
    virtual void doLog(LogEntry const& entry) = 0;

    LogLevel m_logLevel { LogLevel::Verbose };
};

} // namespace jt

#endif // JAMTEMPLATE_LOG_TARGET_BASE_HPP
