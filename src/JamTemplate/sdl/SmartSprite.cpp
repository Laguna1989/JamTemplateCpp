#include "SmartSprite.hpp"
#include "MathHelper.hpp"
#include "SDLHelper.hpp"
#include "TextureManager.hpp"
#include "rendertarget.hpp"
#include <SDL_image.h>

namespace jt {

void SmartSprite::loadSprite(std::string const& fileName)
{
    m_text = TextureManager::get(fileName);
    m_fileName = fileName;
    int w { 0 };
    int h { 0 };
    SDL_QueryTexture(m_text.get(), NULL, NULL, &w, &h); // get the width and height of the texture
    m_sourceRect = jt::recti { 0, 0, w, h };

    m_textFlash = TextureManager::get(TextureManager::getFlashName(fileName));
}

void SmartSprite::loadSprite(std::string const& fileName, jt::recti const& rect)
{
    m_text = TextureManager::get(fileName);
    m_fileName = fileName;
    int w { 0 };
    int h { 0 };
    SDL_QueryTexture(m_text.get(), NULL, NULL, &w, &h); // get the width and height of the texture
    m_sourceRect = jt::recti { rect };

    m_textFlash = TextureManager::get(TextureManager::getFlashName(fileName));
}

void SmartSprite::setPosition(jt::vector2 const& pos) { m_position = pos; }
const jt::vector2 SmartSprite::getPosition() const { return m_position; }

void SmartSprite::setColor(jt::color const& col) { m_color = col; }
const jt::color SmartSprite::getColor() const { return m_color; }

void SmartSprite::setFlashColor(jt::color const& col) { m_colorFlash = col; }
const jt::color SmartSprite::getFlashColor() const { return m_colorFlash; }

//  sf::Transform const getTransform() const  { return m_sprite.getTransform(); }

jt::rect const SmartSprite::getGlobalBounds() const
{
    return jt::rect { 0.0f, 0.0f, static_cast<float>(m_sourceRect.width()),
        static_cast<float>(m_sourceRect.height()) };
}
jt::rect const SmartSprite::getLocalBounds() const
{
    return jt::rect { 0.0f, 0.0f, static_cast<float>(m_sourceRect.width()),
        static_cast<float>(m_sourceRect.height()) };
}

void SmartSprite::setScale(jt::vector2 const& scale) { m_scale = scale; }
const jt::vector2 SmartSprite::getScale() const { return m_scale; }

void SmartSprite::setOrigin(jt::vector2 const& origin) { m_origin = origin; }
jt::vector2 const SmartSprite::getOrigin() const { return m_origin; }

jt::color SmartSprite::getColorAtPixel(jt::vector2u pixelPos) const
{
    if (!m_image) {
        m_image = std::shared_ptr<SDL_Surface>(
            IMG_Load(m_fileName.c_str()), [](SDL_Surface* s) { SDL_FreeSurface(s); });
        if (!m_image) {
            std::cout << "Warning: file could not be loaded for getpixels\n";
            return jt::color { 0, 0, 0, 255 };
        }
    }
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    SDL_GetRGBA(
        jt::getPixel(m_image.get(), pixelPos.x(), pixelPos.y()), m_image->format, &r, &g, &b, &a);
    return jt::color { r, g, b, a };
}

void SmartSprite::cleanImage() { m_image = nullptr; }

void SmartSprite::doUpdate(float /*elapsed*/) { }

void SmartSprite::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Rect sourceRect = getSourceRect();
    SDL_Rect destRect = getDestRect();
    auto flip = jt::getFlipFromScale(m_scale);
    SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(m_color);
    SDL_RenderCopyEx(sptr.get(), m_text.get(), &sourceRect, &destRect, getRotation(), &p, flip);
}

void SmartSprite::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Rect sourceRect = getSourceRect();
    SDL_Rect destRect = getDestRect(getShadowOffset());
    auto flip = jt::getFlipFromScale(m_scale);
    SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(getShadowColor());
    SDL_RenderCopyEx(sptr.get(), m_text.get(), &sourceRect, &destRect, getRotation(), &p, flip);
}

void SmartSprite::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Rect sourceRect = getSourceRect();
    SDL_Rect destRect = getDestRect();
    auto flip = jt::getFlipFromScale(m_scale);
    SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(
        m_textFlash.get(), getFlashColor().r(), getFlashColor().g(), getFlashColor().b());
    SDL_SetTextureAlphaMod(m_textFlash.get(), getFlashColor().a());
    SDL_RenderCopyEx(
        sptr.get(), m_textFlash.get(), &sourceRect, &destRect, getRotation(), &p, flip);
}

void SmartSprite::doRotate(float /*rot*/) { }

SDL_Rect SmartSprite::getDestRect(jt::vector2 const& positionOffset) const
{
    auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset() + positionOffset;
    SDL_Rect destRect { static_cast<int>(pos.x()), static_cast<int>(pos.y()),
        static_cast<int>(m_sourceRect.width() * fabs(m_scale.x())),
        static_cast<int>(m_sourceRect.height() * fabs(m_scale.y())) };
    return destRect;
}
SDL_Rect SmartSprite::getSourceRect() const
{
    return SDL_Rect { m_sourceRect.left(), m_sourceRect.top(), m_sourceRect.width(),
        m_sourceRect.height() };
}

void SmartSprite::setSDLColor(jt::color const& col) const
{
    SDL_SetTextureColorMod(m_text.get(), col.r(), col.g(), col.b());
    SDL_SetTextureAlphaMod(m_text.get(), col.a());
}

} // namespace jt
