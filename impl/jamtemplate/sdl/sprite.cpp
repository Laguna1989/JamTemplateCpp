#include "sprite.hpp"
#include "math_helper.hpp"
#include "render_target.hpp"
#include "sdl_helper.hpp"
#include "texture_manager.hpp"
#include <SDL_image.h>
#include <iostream>
#include <stdexcept>

namespace jt {

void Sprite::loadSprite(std::string const& fileName)
{
    m_text = TextureManager::get(fileName);
    m_fileName = fileName;
    int w { 0 };
    int h { 0 };
    SDL_QueryTexture(
        m_text.get(), nullptr, nullptr, &w, &h); // get the width and height of the texture
    m_sourceRect = jt::Recti { 0, 0, w, h };

    m_textFlash = TextureManager::get(TextureManager::getFlashName(fileName));
}

void Sprite::loadSprite(std::string const& fileName, jt::Recti const& rect)
{
    m_text = TextureManager::get(fileName);
    m_fileName = fileName;
    int w { 0 };
    int h { 0 };
    SDL_QueryTexture(
        m_text.get(), nullptr, nullptr, &w, &h); // get the width and height of the texture
    m_sourceRect = jt::Recti { rect };

    m_textFlash = TextureManager::get(TextureManager::getFlashName(fileName));
}

void Sprite::setPosition(jt::Vector2 const& pos) { m_position = pos; }
jt::Vector2 Sprite::getPosition() const { return m_position; }

void Sprite::setColor(jt::Color const& col) { m_color = col; }
jt::Color Sprite::getColor() const { return m_color; }

void Sprite::setFlashColor(jt::Color const& col) { m_colorFlash = col; }
jt::Color Sprite::getFlashColor() const { return m_colorFlash; }

//  sf::Transform const getTransform() const  { return m_sprite.getTransform(); }

jt::Rect Sprite::getGlobalBounds() const
{
    return jt::Rect { m_position.x(), m_position.y(), static_cast<float>(m_sourceRect.width()),
        static_cast<float>(m_sourceRect.height()) };
}

jt::Rect Sprite::getLocalBounds() const
{
    return jt::Rect { 0.0f, 0.0f, static_cast<float>(m_sourceRect.width()),
        static_cast<float>(m_sourceRect.height()) };
}

void Sprite::setScale(jt::Vector2 const& scale) { m_scale = scale; }
jt::Vector2 Sprite::getScale() const { return m_scale; }

void Sprite::setOrigin(jt::Vector2 const& origin)
{
    m_origin = origin;
    m_offsetFromOrigin = -1.0f * origin;
}

jt::Vector2 Sprite::getOrigin() const { return m_origin; }

jt::Color Sprite::getColorAtPixel(jt::Vector2u pixelPos) const
{
    if (!m_image) {
        m_image = std::shared_ptr<SDL_Surface>(
            IMG_Load(m_fileName.c_str()), [](SDL_Surface* s) { SDL_FreeSurface(s); });
        if (!m_image) {
            std::cout << "Warning: file could not be loaded for getpixels\n";
            return jt::colors::Black;
        }
    }
    if (pixelPos.x() >= static_cast<unsigned int>(m_image->w)
        || pixelPos.y() >= static_cast<unsigned int>(m_image->h)) {
        throw std::invalid_argument { "pixel position out of bounds" };
    }
    uint8_t r = 0u;
    uint8_t g = 0u;
    uint8_t b = 0u;
    uint8_t a = 0u;
    SDL_GetRGBA(
        jt::getPixel(m_image.get(), static_cast<int>(pixelPos.x()), static_cast<int>(pixelPos.y())),
        m_image->format, &r, &g, &b, &a);
    return jt::Color { r, g, b, a };
}

void Sprite::cleanImage() { m_image = nullptr; }

void Sprite::doUpdate(float /*elapsed*/) { }

void Sprite::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Rect const sourceRect = getSourceRect();
    SDL_Rect const destRect = getDestRect();
    auto const flip = jt::getFlipFromScale(m_scale);
    SDL_Point const p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(m_color);
    SDL_RenderCopyEx(sptr.get(), m_text.get(), &sourceRect, &destRect, -getRotation(), &p, flip);
}

void Sprite::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Rect const sourceRect = getSourceRect();
    SDL_Rect const destRect = getDestRect(getShadowOffset());
    auto const flip = jt::getFlipFromScale(m_scale);
    SDL_Point const p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(getShadowColor());
    SDL_RenderCopyEx(sptr.get(), m_text.get(), &sourceRect, &destRect, getRotation(), &p, flip);
}

void Sprite::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Rect const sourceRect = getSourceRect();
    SDL_Rect const destRect = getDestRect();
    auto const flip = jt::getFlipFromScale(m_scale);
    SDL_Point const p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(
        m_textFlash.get(), getFlashColor().r(), getFlashColor().g(), getFlashColor().b());
    SDL_SetTextureAlphaMod(m_textFlash.get(), getFlashColor().a());
    SDL_RenderCopyEx(
        sptr.get(), m_textFlash.get(), &sourceRect, &destRect, getRotation(), &p, flip);
}

void Sprite::doRotate(float /*rot*/) { }

SDL_Rect Sprite::getDestRect(jt::Vector2 const& positionOffset) const
{
    // std::cout << "Sprite.CamOffset.x " << getCamOffset().x() << std::endl;
    auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset() + positionOffset
        + m_offsetFromOrigin;
    // std::cout << "Sprite.final position.x " << pos.x() << std::endl;
    SDL_Rect const destRect { static_cast<int>(pos.x()), static_cast<int>(pos.y()),
        static_cast<int>(static_cast<float>(m_sourceRect.width()) * fabs(m_scale.x())),
        static_cast<int>(static_cast<float>(m_sourceRect.height()) * fabs(m_scale.y())) };
    return destRect;
}

SDL_Rect Sprite::getSourceRect() const
{
    return SDL_Rect { m_sourceRect.left(), m_sourceRect.top(), m_sourceRect.width(),
        m_sourceRect.height() };
}

void Sprite::setSDLColor(jt::Color const& col) const
{
    SDL_SetTextureColorMod(m_text.get(), col.r(), col.g(), col.b());
    SDL_SetTextureAlphaMod(m_text.get(), col.a());
}

} // namespace jt
