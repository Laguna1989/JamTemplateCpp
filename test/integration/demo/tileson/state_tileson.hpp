#ifndef JAMTEMPLATE_DEMOS_TILESON
#define JAMTEMPLATE_DEMOS_TILESON

#include <game_state.hpp>
#include <tilemap/node_layer.hpp>
#include <tilemap/object_layer.hpp>
#include <tileson/actor.hpp>
#include <memory>

namespace jt {
namespace tilemap {

class TileLayer;

}
} // namespace jt

class StateTileson : public jt::GameState {
public:
    StateTileson() = default;
    std::string getName() const override;

private:
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerGround;
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerOverlay;
    bool m_drawTileLayer1 { true };
    bool m_drawTileLayer2 { true };

    std::shared_ptr<jt::tilemap::ObjectLayer> m_objectsLayer;
    bool m_drawObjects { true };

    std::shared_ptr<jt::tilemap::NodeLayer> m_nodeLayer;
    bool m_drawTileNodes { true };

    std::shared_ptr<Actor> m_actor;

    void onCreate() override;
    void onEnter() override;
    void onUpdate(float const elapsed) override;
    void onDraw() const override;
    void moveCamera(float const elapsed);

    void drawObjectLayer() const;
    void drawTileLayers() const;
    void toggleVisibility();
    void drawNodeLayer() const;

    void calculatePath(std::shared_ptr<jt::pathfinder::NodeInterface> start,
        std::shared_ptr<jt::pathfinder::NodeInterface> end);
};

#endif // JAMTEMPLATE_DEMOS_TILESON
