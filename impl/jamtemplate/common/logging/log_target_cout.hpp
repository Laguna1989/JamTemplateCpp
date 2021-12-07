#ifndef MYAWESOMEGAME_LOG_TARGET_COUT_HPP
#define MYAWESOMEGAME_LOG_TARGET_COUT_HPP

#include "log_target_interface.hpp"

namespace jt {
class LogTargetCout : public LogTargetInterface {
public:
    void setLogLevel(LogLevel level) override;
    void log(LogEntry const& entry) override;

private:
    LogLevel m_logLevel { LogLevel::LogLevelDebug };
};
} // namespace jt

#endif // MYAWESOMEGAME_LOG_TARGET_COUT_HPP
