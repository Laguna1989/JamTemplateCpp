#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include "GameState.hpp"
#include <iostream>
#include <memory>
#include <vector>

// fwd decls
namespace jt {
class SmartShape;
class SmartSprite;
} // namespace jt
class b2World;

class Hud;

class StateGame : public jt::GameState {

private:
    std::shared_ptr<jt::SmartShape> m_background;
    std::shared_ptr<jt::SmartShape> m_overlay;
    std::shared_ptr<jt::SmartSprite> m_vignette;
    std::shared_ptr<Hud> m_hud;
    std::shared_ptr<b2World> m_world { nullptr };

    void doInternalCreate() override;
    void doInternalUpdate(float const elapsed) override;
    void doInternalDraw() const override;
};

#endif
