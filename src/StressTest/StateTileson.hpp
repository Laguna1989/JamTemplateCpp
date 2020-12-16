#ifndef STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD

#include "GameState.hpp"
#include <memory>

namespace jt {
class SmartTilemap;
}

class StateTileson : public jt::GameState {
public:
    StateTileson() = default;

private:
    // TODO
    // std::shared_ptr<jt::SmartTilemap> m_tilemap;

    void doCreate() override;
    void doDraw() const override;
    void doUpdate(float const elapsed) override;
};
#endif
