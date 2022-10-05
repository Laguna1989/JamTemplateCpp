#include "graphics_component_impl.hpp"
#include <game_properties.hpp>
#include <math_helper.hpp>

GraphicsComponentImpl::GraphicsComponentImpl(std::shared_ptr<jt::GameInterface> gameInterface)
{
    createAnimation(gameInterface->gfx().textureManager());
}

void GraphicsComponentImpl::createAnimation(jt::TextureManagerInterface& textureManager)
{
    m_animation = std::make_shared<jt::Animation>();
    m_animation->loadFromJson("assets/Pilz.json", textureManager);
    m_animation->play("idle");
}

void GraphicsComponentImpl::updateGraphics(float elapsed) { m_animation->update(elapsed); }

void GraphicsComponentImpl::setPosition(jt::Vector2f const& playerPosition)
{
    auto spritePosition = playerPosition - GP::PlayerSize() * 0.5f;

    m_animation->setPosition(spritePosition);
}

void GraphicsComponentImpl::draw(std::shared_ptr<jt::RenderTargetInterface> target)
{
    m_animation->draw(target);
}

void GraphicsComponentImpl::flash(float time, jt::Color const& color)
{
    m_animation->flash(time, color);
}

bool GraphicsComponentImpl::setAnimationIfNotSet(std::string const& newAnimationName)
{
    std::string const currentAnimationName = m_animation->getCurrentAnimationName();

    if (currentAnimationName == "die") {
        return true;
    }

    if (currentAnimationName == "hurt" && newAnimationName == "idle") {
        return true;
    }

    if (currentAnimationName != newAnimationName) {
        m_animation->play(newAnimationName);
        return true;
    }
    return false;
}

std::string GraphicsComponentImpl::getCurrentAnimation() const
{
    return m_animation->getCurrentAnimationName();
}
