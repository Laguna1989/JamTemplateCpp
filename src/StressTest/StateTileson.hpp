#ifndef STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD

#include "GameState.hpp"
#include <memory>

namespace JamTemplate {
class SmartTilemap;
}

class StateTileson : public JamTemplate::GameState {
public:
    StateTileson() = default;

private:
    std::shared_ptr<JamTemplate::SmartTilemap> m_tilemap;

    void doCreate() override;
    void doDraw() const override;
    void doUpdate(float const elapsed);
};
#endif
