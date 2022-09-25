#ifndef JAMTEMPLATE_DEFAULT_LOGGING_HPP
#define JAMTEMPLATE_DEFAULT_LOGGING_HPP

#include <log/logger_interface.hpp>

namespace jt {

// TODO place in class

/// create a default log target
/// \param logger the logger to be used
void createDefaultLogTargets(LoggerInterface& logger);

} // namespace jt

#endif // JAMTEMPLATE_DEFAULT_LOGGING_HPP
