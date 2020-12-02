#include "SmartShape.hpp"
#include "SDLHelper.hpp"
#include "SmartDrawable.hpp"
#include "TextureManager.hpp"
#include "rect.hpp"
#include "rendertarget.hpp"
#include "vector.hpp"
#include <SDL.h>
#include <memory>
#include <string>

namespace jt {
void SmartShape::makeRect(jt::vector2 size)
{
    m_text = TextureManager::get("#x#" + std::to_string(static_cast<int>(size.x())) + "#"
        + std::to_string(static_cast<int>(size.y())));
    m_sourceRect = jt::recti { 0U, 0U, static_cast<int>(size.x()), static_cast<int>(size.y()) };
}

void SmartShape::setColor(jt::color const& col) { m_color = col; }
const jt::color SmartShape::getColor() const { return m_color; }

void SmartShape::setFlashColor(jt::color const& col) { m_colorFlash = col; }
const jt::color SmartShape::getFlashColor() const { return m_colorFlash; }

void SmartShape::setPosition(jt::vector2 const& pos) { m_position = pos; }
const jt::vector2 SmartShape::getPosition() const { return m_position; }

// sf::Transform const getTransform() const { return m_shape->getTransform(); }

jt::rect const SmartShape::getGlobalBounds() const
{
    return jt::rect { m_position.x(), m_position.y(), m_sourceRect.width() * m_scale.x(),
        m_sourceRect.height() * m_scale.y() };
}
jt::rect const SmartShape::getLocalBounds() const
{
    return jt::rect { m_position.x(), m_position.y(), m_sourceRect.width() * m_scale.x(),
        m_sourceRect.height() * m_scale.y() };
}

void SmartShape::setScale(jt::vector2 const& scale) { m_scale = scale; }
const jt::vector2 SmartShape::getScale() const { return m_scale; }

void SmartShape::setOrigin(jt::vector2 const& origin) { m_origin = origin; }
const jt::vector2 SmartShape::getOrigin() const { return m_origin; }

void SmartShape::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Rect destRect = getDestRect();
    auto flip = jt::getFlipFromScale(m_scale);
    SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(m_color);
    SDL_RenderCopyEx(sptr.get(), m_text.get(), nullptr, &destRect, getRotation(), &p, flip);
}

void SmartShape::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Rect destRect = getDestRect();
    auto flip = jt::getFlipFromScale(m_scale);
    SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(getFlashColor());
    SDL_RenderCopyEx(sptr.get(), m_text.get(), nullptr, &destRect, getRotation(), &p, flip);
}

void SmartShape::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Rect destRect = getDestRect(getShadowOffset());
    auto flip = jt::getFlipFromScale(m_scale);
    SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(getShadowColor());
    SDL_RenderCopyEx(sptr.get(), m_text.get(), nullptr, &destRect, getRotation(), &p, flip);
}

void SmartShape::doUpdate(float /*elapsed*/) { }
void SmartShape::doRotate(float /*rot*/) { }

SDL_Rect SmartShape::getDestRect(jt::vector2 const& positionOffset) const
{
    auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset() + positionOffset;
    SDL_Rect destRect { static_cast<int>(pos.x()), static_cast<int>(pos.y()),
        static_cast<int>(m_sourceRect.width() * fabs(m_scale.x())),
        static_cast<int>(m_sourceRect.height() * fabs(m_scale.y())) };
    return destRect;
}

void SmartShape::setSDLColor(jt::color const& col) const
{
    SDL_SetTextureColorMod(m_text.get(), col.r(), col.g(), col.b());
    SDL_SetTextureAlphaMod(m_text.get(), col.a());
}
} // namespace jt
