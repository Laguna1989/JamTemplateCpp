#ifndef GUARD_JAMTEMPLATE_DEFAULT_LOGGING_HPP
#define GUARD_JAMTEMPLATE_DEFAULT_LOGGING_HPP

#include "log_target_cout.hpp"
#include "log_target_file.hpp"
#include "logger_interface.hpp"

namespace jt {

void createDefaultLogTargets(LoggerInterface& logger);

} // namespace jt

#endif // GUARD_JAMTEMPLATE_DEFAULT_LOGGING_HPP
