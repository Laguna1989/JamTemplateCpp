#pragma once

#include <log/log_level.hpp>
#include <log/log_target_base.hpp>
#include <iostream>
#include <ostream>

namespace jt {
struct LogEntry;

class LogTargetOstream : public LogTargetBase {
public:
    explicit LogTargetOstream(std::ostream& stream = std::cout);

private:
    void doLog(LogEntry const& entry) override;

private:
    std::ostream& m_stream;
};
} // namespace jt
