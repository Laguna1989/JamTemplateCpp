#ifndef JAMTEMPLATE_MOCK_STATE_HPP
#define JAMTEMPLATE_MOCK_STATE_HPP

#include <game_state.hpp>
#include <gmock/gmock.h>

class MockState : public jt::GameState {
public:
    MOCK_METHOD(void, onCreate, ());
    MOCK_METHOD(void, onEnter, (), (override));
    MOCK_METHOD(void, onUpdate, (float));
    MOCK_METHOD(void, onDraw, (), (const));
    MOCK_METHOD(std::string, getName, (), (const, override));
};

#endif // JAMTEMPLATE_MOCK_STATE_HPP
