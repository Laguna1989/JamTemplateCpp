#ifndef JAMTEMPLATE_STATE_SCREEN_EFFECTS_HPP
#define JAMTEMPLATE_STATE_SCREEN_EFFECTS_HPP

#include "screeneffects/stars.hpp"
#include <game_state.hpp>
#include <screeneffects/bubble_smoke.hpp>
#include <screeneffects/clouds.hpp>
#include <screeneffects/mario_clouds.hpp>
#include <screeneffects/particle_system_drop_items.hpp>
#include <screeneffects/scanlines.hpp>
#include <screeneffects/trailing_circles.hpp>
#include <screeneffects/vignette.hpp>
#include <screeneffects/wind_particles.hpp>
#include <sprite.hpp>
#include <tilemap/tile_layer.hpp>
#include <vector>

class StateScreenEffects : public jt::GameState {

    mutable bool m_drawLevel { true };
    std::vector<std::shared_ptr<jt::tilemap::TileLayer>> m_tileLayers {};

    mutable bool m_drawVignette { false };
    std::shared_ptr<jt::Vignette> m_vignette { nullptr };

    mutable bool m_drawScanLines { false };
    std::shared_ptr<jt::ScanLines> m_scanLines { nullptr };

    mutable bool m_drawClouds { false };
    std::shared_ptr<jt::Clouds> m_clouds { nullptr };

    mutable bool m_drawMarioClouds { false };
    std::shared_ptr<jt::MarioClouds> m_marioClouds { nullptr };

    mutable bool m_drawStars { true };
    mutable float m_starsMovementFactor { 1.0f };
    std::shared_ptr<jt::Stars> m_stars { nullptr };

    std::shared_ptr<jt::BubbleSmoke> m_bubbleSmoke { nullptr };

    mutable bool m_drawWind { false };
    mutable float m_windStrength { 1.0f };
    std::shared_ptr<jt::WindParticles> m_wind { nullptr };

    mutable bool m_drawTrailingCircles { false };
    std::shared_ptr<jt::TrailingCircles> m_trailingCircles { nullptr };

    std::shared_ptr<jt::ParticleSystemDropItems> m_dropFruits { nullptr };

    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;

    void scroll(float elapsed);
    void drawGui() const;
};

#endif // JAMTEMPLATE_STATE_SCREEN_EFFECTS_HPP
