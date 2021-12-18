#include "state_select.hpp"
#include "box2d/state_box2d.hpp"
#include "easing/state_easing.hpp"
#include "explosion/state_explosion.hpp"
#include "gradient/state_gradient.hpp"
#include "imgui/state_imgui.hpp"
#include "inventory/state_inventory.hpp"
#include "logging/license_info.hpp"
#include "particles/state_particles.hpp"
#include "pathfinding/state_pathfinding.hpp"
#include "rope/state_rope.hpp"
#include "scroll/state_scroll.hpp"
#include "simplex/state_simplex_noise.hpp"
#include "swarmobjects/state_swarmobjects.hpp"
#include "tileson/state_tileson.hpp"
#include "tween/state_tween.hpp"

void StateSelect::doInternalCreate()
{
    AddButton<StateExplosion>("Explode");
    AddButton<StateSwarmObjects>("Swarm");
    AddButton<StateTween>("Tweens");
    AddButton<StateTileson>("Tilemap");
    AddButton<StateBox2d>("Box2D");
    AddButton<StateScroll>("Move Cam");
    AddButton<StateRope>("Rope");
    AddButton<StateParticles>("Particles");
    AddButton<StatePathfinding>("Pathfinding");
    AddButton<StateGradient>("Palettes");
    AddButton<StateImGui>("ImGui");
    AddButton<StateSimplexNoise>("3D Noise");
    AddButton<StateEasing>("Easing");
    AddButton<StateInventory>("Inventory");

    add(std::make_shared<jt::LicenseInfo>());
}

void StateSelect::doInternalUpdate(float /*elapsed*/)
{
    // nothing to do here
}

void StateSelect::doInternalDraw() const
{
    // nothing to do here
}
std::string StateSelect::getName() const { return "Demo Select"; }
