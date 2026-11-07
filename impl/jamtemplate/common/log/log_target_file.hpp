#pragma once

#include <log/log_level.hpp>
#include <log/log_target_base.hpp>
#include <fstream>

namespace jt {
struct LogEntry;

class LogTargetFile : public LogTargetBase {
public:
    LogTargetFile();

private:
    void doLog(LogEntry const& entry) override;

private:
    std::ofstream m_file;
};

} // namespace jt
