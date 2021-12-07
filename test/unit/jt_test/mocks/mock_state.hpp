#ifndef GUARD_JAMTEMAPLTE_MOCK_STATE_HPP
#define GUARD_JAMTEMAPLTE_MOCK_STATE_HPP

#include "game_state.hpp"
#include <gmock/gmock.h>

class MockState : public jt::GameState {
public:
    MOCK_METHOD(void, doInternalDraw, (), (const));
    MOCK_METHOD(void, doInternalUpdate, (float));
    MOCK_METHOD(void, doInternalCreate, ());
    MOCK_METHOD(std::string, getName, (), (const, override));
};

#endif // GUARD_JAMTEMAPLTE_MOCK_STATE_HPP
