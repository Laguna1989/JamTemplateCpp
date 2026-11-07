#pragma once

#include <log/logger_interface.hpp>

namespace jt {

/// create default log targets (file and cout)
/// \param logger logger to be used
void createDefaultLogTargets(LoggerInterface& logger);

} // namespace jt
