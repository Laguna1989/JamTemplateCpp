#include "player.hpp"
#include <game_interface.hpp>
#include <math_helper.hpp>
#include <player/graphics/graphics_component_impl.hpp>
#include <player/input/input_component_impl.hpp>
#include <player/sound/sound_component_impl.hpp>
#include <state_game.hpp>

namespace {
std::string selectWalkAnimation(jt::Vector2f const& velocity)
{
    std::string walkAnimationName { "idle" };

    if (jt::MathHelper::lengthSquared(velocity) < 2) {
        walkAnimationName = "idle";
    } else if (abs(velocity.x) > abs(velocity.y)) {
        if (velocity.x > 0) {
            walkAnimationName = "right";
        } else {
            walkAnimationName = "left";
        }
    } else {
        if (velocity.y > 0 && abs(velocity.x) < 0.1f) {
            walkAnimationName = "down";
        } else if (velocity.y > 0 && velocity.x > 0) {
            walkAnimationName = "down_right";
        } else if (velocity.y > 0 && velocity.x < 0) {
            walkAnimationName = "down_left";
        } else {
            walkAnimationName = "up";
        }
    }

    return walkAnimationName;
}
} // namespace

Player::Player(
    std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def, StateGame& state)
    : jt::Box2DObject { world, def }
    , m_state { state }
{
}

void Player::doCreate()
{
    m_input = std::make_unique<InputComponentImpl>(getGame()->input().keyboard());
    m_sound = std::make_unique<SoundComponentImpl>(getGame()->audio(), getGame()->logger());
    m_graphics = std::make_unique<GraphicsComponentImpl>(getGame());
}

void Player::doUpdate(float const elapsed)
{
    m_input->updateMovement(*this);
    m_graphics->setPosition(getPosition());

    m_graphics->setAnimationIfNotSet(selectWalkAnimation(getVelocity()));
    m_graphics->updateGraphics(elapsed);
}
void Player::doDraw() const { m_graphics->draw(renderTarget()); }
