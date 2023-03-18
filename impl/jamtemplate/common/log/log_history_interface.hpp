#ifndef JAMTEMPLATE_LOG_HISTORY_INTERFACE_HPP
#define JAMTEMPLATE_LOG_HISTORY_INTERFACE_HPP

#include <log/log_entry.hpp>
#include <vector>

namespace jt {

class LogHistoryInterface {
public:
    virtual ~LogHistoryInterface() = default;

    /// Add a log entry to the history
    /// \param entry the entry to be added
    virtual void addEntry(jt::LogEntry const& entry) = 0;

    /// Get the history of log entries
    /// \return the vector of LogEntries
    virtual std::vector<jt::LogEntry> const& getHistory() = 0;

    /// Clear all log entries
    virtual void clear() = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_LOG_HISTORY_INTERFACE_HPP
