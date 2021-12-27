#include "default_logging.hpp"

namespace jt {

void createDefaultLogTargets(LoggerInterface& logger)
{
    auto targetCout = std::make_shared<LogTargetCout>();
    targetCout->setLogLevel(LogLevel::LogLevelInfo);

    logger.addLogTarget(targetCout);
    logger.addLogTarget(std::make_shared<LogTargetFile>());
    logger.setLogLevel(LogLevel::LogLevelDebug);
}

} // namespace jt
