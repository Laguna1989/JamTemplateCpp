#ifndef STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD

#include "GameState.hpp"
#include "SmartTilemap.hpp"
#include "Sound.hpp"
#include <memory>

namespace jt {
class SmartTilemap;
}

class StateTileson : public jt::GameState {
public:
    StateTileson() = default;

private:
    std::shared_ptr<jt::SmartTilemap> m_tilemap;

    std::shared_ptr<jt::Sound> m_sound;

    void doInternalCreate() override;
    void doInternalUpdate(float const elapsed) override;
    void doInternalDraw() const override;
};
#endif
