﻿#ifndef STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD

#include "game_state.hpp"
#include <memory>
#include <tilemap/node_layer.hpp>
#include <tilemap/object_layer.hpp>

namespace jt {
namespace tilemap {

class TileLayer;

}
} // namespace jt

class StateTileson : public jt::GameState {
public:
    StateTileson() = default;

private:
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerGround;
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerOverlay;
    bool m_drawTileLayer1 { true };
    bool m_drawTileLayer2 { true };

    std::shared_ptr<jt::tilemap::ObjectLayer> m_objectsLayer;
    bool m_drawObjects { true };

    std::shared_ptr<jt::tilemap::NodeLayer> m_nodeLayer;
    bool m_drawTileNodes { true };

    void doInternalCreate() override;
    void doInternalUpdate(float const elapsed) override;
    void doInternalDraw() const override;
    void moveCamera(float const elapsed);

    void drawObjectLayer() const;
    void drawTileLayers() const;
    void toggleVisibility();
    void drawNodeLayer() const;

    void calculatePath(std::shared_ptr<jt::pathfinder::NodeInterface> start,
        std::shared_ptr<jt::pathfinder::NodeInterface> end);
};
#endif