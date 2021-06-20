#ifndef STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD

#include "game_state.hpp"
#include <memory>

namespace jt {
class Tilemap;
class Sound;
} // namespace jt

class StateTileson : public jt::GameState {
public:
    StateTileson() = default;

private:
    std::shared_ptr<jt::Tilemap> m_tilemap;

    std::shared_ptr<jt::Sound> m_sound;

    void doInternalCreate() override;
    void doInternalUpdate(float const elapsed) override;
    void doInternalDraw() const override;
};
#endif
