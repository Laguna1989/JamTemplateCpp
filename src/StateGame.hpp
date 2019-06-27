#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include <iostream>
#include <memory>
#include <vector>

#include "JamTemplate/GameState.hpp"

// fwd decls
namespace JamTemplate {
class SmartShape;
}

class Hud;

class StateGame : public JamTemplate::GameState {
public:
    StateGame() = default;

protected:
    std::shared_ptr<Hud> m_hud;

private:
    std::shared_ptr<JamTemplate::SmartShape> m_background;
    std::shared_ptr<JamTemplate::SmartShape> m_overlay;

    void doCreate() override;

    virtual void doCreateInternal();

    virtual void doInternalUpdate(float const elapsed) override;
    virtual void doInternalDraw() const override;
};

#endif
