#ifndef JAMTEMPLATE_STATE_STORE_GAMESTATE_HPP
#define JAMTEMPLATE_STATE_STORE_GAMESTATE_HPP

#include <game_state.hpp>

class StateStoreGamestate : public jt::GameState {
private:
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;

    virtual std::string getName() const override;

    mutable int m_value = 0;
};

#endif // JAMTEMPLATE_STATE_STORE_GAMESTATE_HPP
