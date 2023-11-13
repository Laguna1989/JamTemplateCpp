#include "log_history.hpp"

std::vector<jt::LogEntry> const& jt::LogHistory::getHistory() { return m_history; }

void jt::LogHistory::clear() { m_history.clear(); }

void jt::LogHistory::doLog(jt::LogEntry const& entry)
{
    m_history.push_back(entry);

    if (m_history.size() > m_historyMaxSize) {
        m_history.erase(m_history.begin(), m_history.begin() + m_historyResizeTo + 1);
    }
}
