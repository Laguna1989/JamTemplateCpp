#include "SmartSprite.hpp"
#include "MathHelper.hpp"
#include "Rendertarget.hpp"
#include "SDLHelper.hpp"
#include "TextureManager.hpp"
#include <SDL_image.h>

namespace jt {

void SmartSprite::loadSprite(std::string const& fileName)
{
    m_text = TextureManager::get(fileName);
    m_fileName = fileName;
    int w { 0 };
    int h { 0 };
    SDL_QueryTexture(m_text.get(), NULL, NULL, &w, &h); // get the width and height of the texture
    m_sourceRect = jt::Recti { 0, 0, w, h };

    m_textFlash = TextureManager::get(TextureManager::getFlashName(fileName));
}

void SmartSprite::loadSprite(std::string const& fileName, jt::Recti const& rect)
{
    m_text = TextureManager::get(fileName);
    m_fileName = fileName;
    int w { 0 };
    int h { 0 };
    SDL_QueryTexture(m_text.get(), NULL, NULL, &w, &h); // get the width and height of the texture
    m_sourceRect = jt::Recti { rect };

    m_textFlash = TextureManager::get(TextureManager::getFlashName(fileName));
}

void SmartSprite::setPosition(jt::Vector2 const& pos) { m_position = pos; }
const jt::Vector2 SmartSprite::getPosition() const { return m_position; }

void SmartSprite::setColor(jt::Color const& col) { m_color = col; }
const jt::Color SmartSprite::getColor() const { return m_color; }

void SmartSprite::setFlashColor(jt::Color const& col) { m_colorFlash = col; }
const jt::Color SmartSprite::getFlashColor() const { return m_colorFlash; }

//  sf::Transform const getTransform() const  { return m_sprite.getTransform(); }

jt::Rect const SmartSprite::getGlobalBounds() const
{
    return jt::Rect { 0.0f, 0.0f, static_cast<float>(m_sourceRect.width()),
        static_cast<float>(m_sourceRect.height()) };
}
jt::Rect const SmartSprite::getLocalBounds() const
{
    return jt::Rect { 0.0f, 0.0f, static_cast<float>(m_sourceRect.width()),
        static_cast<float>(m_sourceRect.height()) };
}

void SmartSprite::setScale(jt::Vector2 const& scale) { m_scale = scale; }
const jt::Vector2 SmartSprite::getScale() const { return m_scale; }

void SmartSprite::setOrigin(jt::Vector2 const& origin) { m_origin = origin; }
jt::Vector2 const SmartSprite::getOrigin() const { return m_origin; }

jt::Color SmartSprite::getColorAtPixel(jt::Vector2u pixelPos) const
{
    if (!m_image) {
        m_image = std::shared_ptr<SDL_Surface>(
            IMG_Load(m_fileName.c_str()), [](SDL_Surface* s) { SDL_FreeSurface(s); });
        if (!m_image) {
            std::cout << "Warning: file could not be loaded for getpixels\n";
            return jt::Color { 0, 0, 0, 255 };
        }
    }
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    SDL_GetRGBA(
        jt::getPixel(m_image.get(), pixelPos.x(), pixelPos.y()), m_image->format, &r, &g, &b, &a);
    return jt::Color { r, g, b, a };
}

void SmartSprite::cleanImage() { m_image = nullptr; }

void SmartSprite::doUpdate(float /*elapsed*/) { }

void SmartSprite::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Rect const sourceRect = getSourceRect();
    SDL_Rect const destRect = getDestRect();
    auto const flip = jt::getFlipFromScale(m_scale);
    SDL_Point const p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(m_color);
    SDL_RenderCopyEx(sptr.get(), m_text.get(), &sourceRect, &destRect, getRotation(), &p, flip);
}

void SmartSprite::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Rect const sourceRect = getSourceRect();
    SDL_Rect const destRect = getDestRect(getShadowOffset());
    auto const flip = jt::getFlipFromScale(m_scale);
    SDL_Point const p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    setSDLColor(getShadowColor());
    SDL_RenderCopyEx(sptr.get(), m_text.get(), &sourceRect, &destRect, getRotation(), &p, flip);
}

void SmartSprite::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
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

void SmartSprite::doRotate(float /*rot*/) { }

SDL_Rect SmartSprite::getDestRect(jt::Vector2 const& positionOffset) const
{
    // std::cout << "SmartSprite.CamOffset.x " << getCamOffset().x() << std::endl;
    auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset() + positionOffset;
    // std::cout << "SmartSprite.final position.x " << pos.x() << std::endl;
    SDL_Rect const destRect { static_cast<int>(pos.x()), static_cast<int>(pos.y()),
        static_cast<int>(m_sourceRect.width() * fabs(m_scale.x())),
        static_cast<int>(m_sourceRect.height() * fabs(m_scale.y())) };
    return destRect;
}

SDL_Rect SmartSprite::getSourceRect() const
{
    return SDL_Rect { m_sourceRect.left(), m_sourceRect.top(), m_sourceRect.width(),
        m_sourceRect.height() };
}

void SmartSprite::setSDLColor(jt::Color const& col) const
{
    SDL_SetTextureColorMod(m_text.get(), col.r(), col.g(), col.b());
    SDL_SetTextureAlphaMod(m_text.get(), col.a());
}

} // namespace jt
