#include "default_logging.hpp"
#include <log/log_target_cout.hpp>
#include <log/log_target_file.hpp>

void jt::createDefaultLogTargets(jt::LoggerInterface& logger)
{
    auto targetCout = std::make_shared<jt::LogTargetCout>();
    targetCout->setLogLevel(LogLevel::LogLevelInfo);

    logger.addLogTarget(targetCout);
    logger.addLogTarget(std::make_shared<jt::LogTargetFile>());
    logger.setLogLevel(LogLevel::LogLevelDebug);
}