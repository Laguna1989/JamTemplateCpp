#ifndef JAMTEMPLATE_LOG_TARGET_FILE_HPP
#define JAMTEMPLATE_LOG_TARGET_FILE_HPP

#include <log/log_target_interface.hpp>
#include <fstream>

namespace jt {

class LogTargetFile : public LogTargetInterface {
public:
    LogTargetFile();
    void log(LogEntry const& entry) override;
    void setLogLevel(LogLevel level) override;

private:
    std::ofstream m_file;
    LogLevel m_logLevel { LogLevel::LogLevelVerbose };
};

} // namespace jt

#endif // JAMTEMPLATE_LOG_TARGET_FILE_HPP
