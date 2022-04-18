#ifndef JAMTEMPLATE_STATE_SCREEN_EFFECTS_HPP
#define JAMTEMPLATE_STATE_SCREEN_EFFECTS_HPP

#include <game_state.hpp>
#include <screeneffects/clouds.hpp>
#include <screeneffects/scanlines.hpp>
#include <screeneffects/vignette.hpp>
#include <sprite.hpp>
#include <tilemap/tile_layer.hpp>
#include <vector>

class StateScreenEffects : public jt::GameState {
    std::vector<std::shared_ptr<jt::tilemap::TileLayer>> m_tileLayers {};

    mutable bool m_drawVignette { true };
    std::shared_ptr<jt::Vignette> m_vignette { nullptr };

    mutable bool m_drawScanLines { true };
    std::shared_ptr<jt::ScanLines> m_scanLines { nullptr };

    mutable bool m_drawClouds { true };
    std::shared_ptr<jt::Clouds> m_clouds { nullptr };

    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
    void scroll(float elapsed);
    void drawGui() const;
};

#endif // JAMTEMPLATE_STATE_SCREEN_EFFECTS_HPP
