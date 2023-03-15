#ifndef STRESSTEST_STATE_1_HPP
#define STRESSTEST_STATE_1_HPP

#include <game_state.hpp>
#include <string>

class StateExplosion : public jt::GameState {
public:
    std::string getName() const override;

private:
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float const /*elapsed*/) override;
    void onDraw() const override {};
};

#endif
