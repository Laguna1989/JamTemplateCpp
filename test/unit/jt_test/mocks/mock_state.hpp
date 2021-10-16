#ifndef MYAWESOMEGAME_MOCK_STATE_HPP
#define MYAWESOMEGAME_MOCK_STATE_HPP

#include "game_state.hpp"
#include <gmock/gmock.h>

class MockState : public jt::GameState {
public:
    MOCK_METHOD(void, doInternalDraw, (), (const));
    MOCK_METHOD(void, doInternalUpdate, (float));
    MOCK_METHOD(void, doInternalCreate, ());
};

#endif // MYAWESOMEGAME_MOCK_STATE_HPP
