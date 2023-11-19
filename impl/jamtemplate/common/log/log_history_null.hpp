#ifndef JAMTEMPLATE_LOG_HISTORY_NULL_HPP
#define JAMTEMPLATE_LOG_HISTORY_NULL_HPP

#include <log/log_history_interface.hpp>

namespace jt {
namespace null_objects {

class LogHistoryNull : public jt::LogHistoryInterface {
public:
    std::vector<jt::LogEntry> const& getHistory() override;
    void clear() override;

private:
    std::vector<jt::LogEntry> m_history;
};

} // namespace null_objects

} // namespace jt

#endif // JAMTEMPLATE_LOG_HISTORY_NULL_HPP
