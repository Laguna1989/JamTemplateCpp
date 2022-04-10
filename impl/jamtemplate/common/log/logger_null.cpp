#include "logger_null.hpp"

void jt::null_objects::LoggerNull::action(std::string const& /*string*/) { }

void jt::null_objects::LoggerNull::fatal(
    std::string const& /*string*/, std::vector<std::string> /*tags*/)
{
}
void jt::null_objects::LoggerNull::error(
    std::string const& /*string*/, std::vector<std::string> /*tags*/)
{
}
void jt::null_objects::LoggerNull::warning(
    std::string const& /*string*/, std::vector<std::string> /*tags*/)
{
}
void jt::null_objects::LoggerNull::info(
    std::string const& /*string*/, std::vector<std::string> /*tags*/)
{
}
void jt::null_objects::LoggerNull::debug(
    std::string const& /*string*/, std::vector<std::string> /*tags*/)
{
}
void jt::null_objects::LoggerNull::verbose(
    std::string const& /*string*/, std::vector<std::string> /*tags*/)
{
}
void jt::null_objects::LoggerNull::addLogTarget(std::shared_ptr<LogTargetInterface> /*target*/) { }
std::vector<jt::LogEntry> const& jt::null_objects::LoggerNull::getHistory() { return m_history; }
void jt::null_objects::LoggerNull::setLogLevel(LogLevel /*level*/) { }
void jt::null_objects::LoggerNull::clear() { }
