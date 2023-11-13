
#include "log_history_null.hpp"

namespace jt {

std::vector<jt::LogEntry> const& null_objects::LogHistoryNull::getHistory() { return m_history; }

void null_objects::LogHistoryNull::clear() { }
} // namespace jt
