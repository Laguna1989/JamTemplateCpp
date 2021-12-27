#ifndef GUARD_JAMTEMPLATE_MOCK_LOGGER_HPP
#define GUARD_JAMTEMPLATE_MOCK_LOGGER_HPP

#include "logging/logger_interface.hpp"
#include <gmock/gmock.h>

class MockLogger : public jt::LoggerInterface {
public:
    MOCK_METHOD(void, fatal, (std::string const&, std::vector<std::string>), (override));
    MOCK_METHOD(void, error, (std::string const&, std::vector<std::string>), (override));
    MOCK_METHOD(void, warning, (std::string const&, std::vector<std::string>), (override));
    MOCK_METHOD(void, info, (std::string const&, std::vector<std::string>), (override));
    MOCK_METHOD(void, debug, (std::string const&, std::vector<std::string>), (override));
    MOCK_METHOD(void, verbose, (std::string const&, std::vector<std::string>), (override));
    MOCK_METHOD(void, action, (std::string const&), (override));
    MOCK_METHOD(void, addLogTarget, (std::shared_ptr<jt::LogTargetInterface>), (override));
    MOCK_METHOD(std::vector<jt::LogEntry> const&, getHistory, (), (override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(void, setLogLevel, (LogLevel), (override));
};

#endif // GUARD_JAMTEMPLATE_MOCK_LOGGER_HPP
