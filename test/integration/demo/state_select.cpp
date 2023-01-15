#include "state_select.hpp"
#include "offset_origin/state_offset_origin.hpp"
#include "palette/state_palette.hpp"
#include <audio/state_audio.hpp>
#include <box2d/state_box2d.hpp>
#include <easing/state_easing.hpp>
#include <explosion/state_explosion.hpp>
#include <gamepad/state_gamepad.hpp>
#include <imgui/state_imgui.hpp>
#include <inventory/state_inventory.hpp>
#include <log/license_info.hpp>
#include <particles/state_particles.hpp>
#include <pathfinding/state_pathfinding.hpp>
#include <rope/state_rope.hpp>
#include <screeneffects/state_screen_effects.hpp>
#include <scroll/state_scroll.hpp>
#include <simplex/state_3d_noise.hpp>
#include <swarmobjects/state_swarmobjects.hpp>
#include <tilemap_effects/state_tilemap_effects.hpp>
#include <tileson/state_tileson.hpp>
#include <transitions/state_transitions.hpp>
#include <tween/state_tween.hpp>

void StateSelect::doInternalCreate()
{
    AddButton<StateExplosion>("Explode");
    AddButton<StateSwarmObjects>("Swarm");
    AddButton<StateTween>("Tweens");
    AddButton<StateTileson>("Tilemap");
    AddButton<StatePlatformer>("Box2D");
    AddButton<StateScroll>("Move Cam");
    AddButton<StateRope>("Rope");
    AddButton<StateParticles>("Particles");
    AddButton<StatePathfinding>("Pathfinding");
    AddButton<StatePalette>("Palettes");
    AddButton<StateImGui>("ImGui");
    AddButton<State3DNoise>("3D Noise");
    AddButton<StateEasing>("Easing");
    AddButton<StateInventory>("Inventory");
    AddButton<StateAudio>("Audio");
    AddButton<StateGamepad>("Gamepad");
    AddButton<StateTransitions>("Transitions");
    AddButton<StateScreenEffects>("Effects");
    AddButton<StateTilemapEffects>("Tile Effects");
    AddButton<StateOffsetOrigin>("offset origin");

    add(std::make_shared<jt::LicenseInfo>());
}

void StateSelect::doInternalUpdate(float /*elapsed*/) { }

void StateSelect::doInternalDraw() const { }
std::string StateSelect::getName() const { return "State Demo Select"; }
