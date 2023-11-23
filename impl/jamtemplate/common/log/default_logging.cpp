#include "default_logging.hpp"
#include <log/log_target_file.hpp>
#include <log/log_target_ostream.hpp>

void jt::createDefaultLogTargets(jt::LoggerInterface& logger)
{
    auto targetCout = std::make_shared<jt::LogTargetOstream>();
    targetCout->setLogLevel(LogLevel::Info);

    logger.addLogTarget(targetCout);
    logger.addLogTarget(std::make_shared<jt::LogTargetFile>());
    logger.setLogLevel(LogLevel::Debug);
}
