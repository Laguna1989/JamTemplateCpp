#ifndef JAMTEMPLATE_LOG_HISTORY_INTERFACE_HPP
#define JAMTEMPLATE_LOG_HISTORY_INTERFACE_HPP

#include <log/log_entry.hpp>
#include <vector>

namespace jt {

class LogHistoryInterface {
public:
    /// Get the history of log entries
    /// \return the vector of LogEntries
    virtual std::vector<jt::LogEntry> const& getHistory() = 0;

    /// Clear all log entries
    virtual void clear() = 0;

    /// Destructor
    virtual ~LogHistoryInterface() = default;

    // no copy, no move. Avoid slicing.
    LogHistoryInterface(LogHistoryInterface const&) = delete;
    LogHistoryInterface(LogHistoryInterface&&) = delete;
    LogHistoryInterface& operator=(LogHistoryInterface const&) = delete;
    LogHistoryInterface& operator=(LogHistoryInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    LogHistoryInterface() = default;
};
} // namespace jt

#endif // JAMTEMPLATE_LOG_HISTORY_INTERFACE_HPP
