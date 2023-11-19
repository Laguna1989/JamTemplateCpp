#ifndef JAMTEMPLATE_LOG_HISTORY_HPP
#define JAMTEMPLATE_LOG_HISTORY_HPP

#include <log/log_history_interface.hpp>
#include <log/log_target_base.hpp>

namespace jt {
class LogHistory : public jt::LogHistoryInterface, public jt::LogTargetBase {
public:
    std::vector<jt::LogEntry> const& getHistory() override;
    void clear() override;

    std::size_t const m_historyMaxSize { 300u };
    std::size_t const m_historyResizeTo { 150u };

private:
    std::vector<LogEntry> m_history;

    void doLog(LogEntry const& entry) override;
};
} // namespace jt
#endif // JAMTEMPLATE_LOG_HISTORY_HPP
