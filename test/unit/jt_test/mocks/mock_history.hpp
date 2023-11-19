#ifndef JAMTEMPLATE_MOCK_HISTORY_HPP
#define JAMTEMPLATE_MOCK_HISTORY_HPP

#include <log/log_history_interface.hpp>
#include <gmock/gmock.h>

class MockHistory : public jt::LogHistoryInterface {
public:
    MOCK_METHOD(std::vector<jt::LogEntry> const&, getHistory, (), (override));
    MOCK_METHOD(void, clear, (), (override));
};

#endif // JAMTEMPLATE_MOCK_HISTORY_HPP
