#ifndef JAMTEMPLATE_STATE_STORE_GAMESTATE_HPP
#define JAMTEMPLATE_STATE_STORE_GAMESTATE_HPP

#include <game_state.hpp>

class StateStoreGamestate : public jt::GameState {
private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    virtual std::string getName() const override;

    mutable int m_value = 0;
};

#endif // JAMTEMPLATE_STATE_STORE_GAMESTATE_HPP
