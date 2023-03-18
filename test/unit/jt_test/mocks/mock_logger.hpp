#ifndef JAMTEMPLATE_MOCK_LOGGER_HPP
#define JAMTEMPLATE_MOCK_LOGGER_HPP

#include <log/log_entry.hpp>
#include <log/log_level.hpp>
#include <log/log_target_interface.hpp>
#include <log/logger_interface.hpp>
#include <gmock/gmock.h>

class MockLogger : public jt::LoggerInterface {
public:
    MOCK_METHOD(void, fatal, (std::string const&, std::vector<std::string> const&), (override));
    MOCK_METHOD(void, error, (std::string const&, std::vector<std::string> const&), (override));
    MOCK_METHOD(void, warning, (std::string const&, std::vector<std::string> const&), (override));
    MOCK_METHOD(void, info, (std::string const&, std::vector<std::string> const&), (override));
    MOCK_METHOD(void, debug, (std::string const&, std::vector<std::string> const&), (override));
    MOCK_METHOD(void, verbose, (std::string const&, std::vector<std::string> const&), (override));
    MOCK_METHOD(void, action, (std::string const&), (override));
    MOCK_METHOD(void, addLogTarget, (std::shared_ptr<jt::LogTargetInterface>), (override));
    MOCK_METHOD(void, setLogLevel, (jt::LogLevel), (override));
};

#endif // JAMTEMPLATE_MOCK_LOGGER_HPP
