#ifndef STRESSTEST_STATE_SELECT_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_SELECT_HPP_INCLUDEGUARD

#include "GameState.hpp"

class StateSelect : public jt::GameState {

private:
    virtual void doInternalCreate() override;
    virtual void doInternalUpdate(float elapsed) override;
    virtual void doInternalDraw() const override;
};

#endif