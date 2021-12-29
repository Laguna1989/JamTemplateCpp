#include "shape.hpp"
#include "rect.hpp"
#include "render_target.hpp"
#include "sdl_helper.hpp"
#include "vector.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <string>

namespace jt {
void Shape::makeRect(jt::Vector2f size, jt::TextureManagerInterface& textureManager)
{
    m_text = textureManager.get("#x#" + std::to_string(static_cast<int>(size.x)) + "#"
        + std::to_string(static_cast<int>(size.y)));
    m_sourceRect = jt::Recti { 0U, 0U, static_cast<int>(size.x), static_cast<int>(size.y) };
}

void Shape::makeCircle(float radius, jt::TextureManagerInterface& textureManager)
{
    m_text = textureManager.get("#c#" + std::to_string(static_cast<int>(radius)));
    m_sourceRect
        = jt::Recti { 0U, 0U, static_cast<int>(radius * 2.0f), static_cast<int>(radius * 2.0f) };
}

void Shape::setColor(jt::Color const& col) { m_color = col; }
jt::Color Shape::getColor() const { return m_color; }

void Shape::setFlashColor(jt::Color const& col) { m_colorFlash = col; }
jt::Color Shape::getFlashColor() const { return m_colorFlash; }

void Shape::setPosition(jt::Vector2f const& pos) { m_position = pos; }
jt::Vector2f Shape::getPosition() const { return m_position; }

jt::Rectf Shape::getGlobalBounds() const
{
    return jt::Rectf { m_position.x + getOffset().x, m_position.y + getOffset().y,
        static_cast<float>(m_sourceRect.width) * m_scale.x,
        static_cast<float>(m_sourceRect.height) * m_scale.y };
}
jt::Rectf Shape::getLocalBounds() const
{
    return jt::Rectf { m_position.x, m_position.y,
        static_cast<float>(m_sourceRect.width) * m_scale.x,
        static_cast<float>(m_sourceRect.height) * m_scale.y };
}

void Shape::setScale(jt::Vector2f const& scale) { m_scale = scale; }
jt::Vector2f Shape::getScale() const { return m_scale; }

void Shape::setOrigin(jt::Vector2f const& origin)
{
    m_origin = origin;
    m_offsetFromOrigin = -1.0f * origin;
}
jt::Vector2f Shape::getOrigin() const { return m_origin; }

void Shape::doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    SDL_Rect const destRect = getDestRect();
    auto const flip = jt::getFlipFromScale(m_scale);
    SDL_Point const p { static_cast<int>(m_origin.x), static_cast<int>(m_origin.y) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(m_color);
    SDL_RenderCopyEx(sptr.get(), m_text.get(), nullptr, &destRect, getRotation(), &p, flip);
}

void Shape::doDrawFlash(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    SDL_Rect const destRect = getDestRect();
    auto const flip = jt::getFlipFromScale(m_scale);
    SDL_Point const p { static_cast<int>(m_origin.x), static_cast<int>(m_origin.y) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(getFlashColor());
    SDL_RenderCopyEx(sptr.get(), m_text.get(), nullptr, &destRect, getRotation(), &p, flip);
}

void Shape::doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    SDL_Rect const destRect = getDestRect(getShadowOffset());
    auto const flip = jt::getFlipFromScale(m_scale);
    SDL_Point const p { static_cast<int>(m_origin.x), static_cast<int>(m_origin.y) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(getShadowColor());
    SDL_RenderCopyEx(sptr.get(), m_text.get(), nullptr, &destRect, getRotation(), &p, flip);
}

void Shape::doUpdate(float /*elapsed*/) { }
void Shape::doRotate(float /*rot*/) { }

SDL_Rect Shape::getDestRect(jt::Vector2f const& positionOffset) const
{
    auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset() + positionOffset
        + m_offsetFromOrigin;
    SDL_Rect const destRect { static_cast<int>(pos.x), static_cast<int>(pos.y),
        static_cast<int>(static_cast<float>(m_sourceRect.width) * fabs(m_scale.x)),
        static_cast<int>(static_cast<float>(m_sourceRect.height) * fabs(m_scale.y)) };
    return destRect;
}

void Shape::setSDLColor(jt::Color const& col) const
{
    SDL_SetTextureColorMod(m_text.get(), col.r, col.g, col.b);
    SDL_SetTextureAlphaMod(m_text.get(), col.a);
}
} // namespace jt
