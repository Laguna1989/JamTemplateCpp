#ifndef MYAWESOMEGAME_MOCK_LOG_TARGET_HPP
#define MYAWESOMEGAME_MOCK_LOG_TARGET_HPP

#include <log/log_target_interface.hpp>
#include <gmock/gmock.h>

class MockLogTarget : public jt::LogTargetInterface {
public:
    MOCK_METHOD(void, log, (jt::LogEntry const&), (override));
    MOCK_METHOD(void, setLogLevel, (LogLevel), (override));
};

#endif // MYAWESOMEGAME_MOCK_LOG_TARGET_HPP
