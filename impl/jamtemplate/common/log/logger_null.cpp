#include "logger_null.hpp"
#include <log/log_target_interface.hpp>

void jt::null_objects::LoggerNull::action(
    std::string const& /*string*/)
{
}

void jt::null_objects::LoggerNull::fatal(std::string const& /*string*/,
    std::vector<std::string> const& /*tags*/ )
{
}

void jt::null_objects::LoggerNull::error(std::string const& /*string*/,
    std::vector<std::string> const& /*tags*/ )
{
}

void jt::null_objects::LoggerNull::warning(std::string const& /*string*/,
    std::vector<std::string> const& /*tags*/ )
{
}

void jt::null_objects::LoggerNull::info(std::string const& /*string*/,
    std::vector<std::string> const& /*tags*/ )
{
}

void jt::null_objects::LoggerNull::debug(std::string const& /*string*/,
    std::vector<std::string> const& /*tags*/ )
{
}

void jt::null_objects::LoggerNull::verbose(std::string const& /*string*/,
    std::vector<std::string> const& /*tags*/ )
{
}

void jt::null_objects::LoggerNull::addLogTarget(std::shared_ptr<LogTargetInterface> /*target*/) { }

void jt::null_objects::LoggerNull::setLogLevel(LogLevel /*level*/) { }
