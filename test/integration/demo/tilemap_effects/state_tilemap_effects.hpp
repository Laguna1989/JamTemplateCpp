#ifndef JAMTEMPLATE_DEMOS_STATE_TILEMAP_EFFECTS
#define JAMTEMPLATE_DEMOS_STATE_TILEMAP_EFFECTS

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

class StateTilemapEffects : public jt::GameState {
public:
    std::string getName() const override;

private:
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerGround;

    mutable float m_rotation { 0.0f };
    mutable float m_scaleX { 1.0f };
    mutable float m_scaleY { 1.0f };

    mutable float m_time { 0.0f };

    void onCreate() override;
    void onEnter() override;
    void onUpdate(float const elapsed) override;
    void onDraw() const override;
    void moveCamera(float const elapsed);
};

#endif // JAMTEMPLATE_DEMOS_STATE_TILEMAP_EFFECTS
