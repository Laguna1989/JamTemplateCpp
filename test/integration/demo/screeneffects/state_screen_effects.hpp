#ifndef JAMTEMPLATE_STATE_SCREEN_EFFECTS_HPP
#define JAMTEMPLATE_STATE_SCREEN_EFFECTS_HPP

#include "screeneffects/stars.hpp"
#include "screeneffects/wind_particles.hpp"
#include <game_state.hpp>
#include <screeneffects/bubble_smoke.hpp>
#include <screeneffects/clouds.hpp>
#include <screeneffects/scanlines.hpp>
#include <screeneffects/vignette.hpp>
#include <sprite.hpp>
#include <tilemap/tile_layer.hpp>
#include <vector>

class StateScreenEffects : public jt::GameState {

    mutable bool m_drawLevel { true };
    std::vector<std::shared_ptr<jt::tilemap::TileLayer>> m_tileLayers {};

    mutable bool m_drawVignette { true };
    std::shared_ptr<jt::Vignette> m_vignette { nullptr };

    mutable bool m_drawScanLines { true };
    std::shared_ptr<jt::ScanLines> m_scanLines { nullptr };

    mutable bool m_drawClouds { true };
    std::shared_ptr<jt::Clouds> m_clouds { nullptr };

    mutable bool m_drawStars { true };
    mutable float m_starsMovementFactor { 1.0f };
    std::shared_ptr<jt::Stars> m_stars { nullptr };

    std::shared_ptr<jt::BubbleSmoke> m_bubbleSmoke { nullptr };

    mutable bool m_drawWind { true };
    mutable float m_windStrength { 1.0f };
    std::shared_ptr<jt::WindParticles> m_wind { nullptr };

    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
    void scroll(float elapsed);
    void drawGui() const;
};

#endif // JAMTEMPLATE_STATE_SCREEN_EFFECTS_HPP
