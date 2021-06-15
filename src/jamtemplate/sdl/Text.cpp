
#include "Text.hpp"
#include "Rendertarget.hpp"
#include "SDLHelper.hpp"
#include "SplitString.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <exception>

namespace jt {

Text::~Text()
{
    if (m_font != nullptr) {
        TTF_CloseFont(m_font);
    }
}

void Text::loadFont(std::string const& fontFileName, unsigned int characterSize,
    std::weak_ptr<jt::renderTarget> wptr)
{
    m_font = TTF_OpenFont(fontFileName.c_str(), characterSize * getUpscaleFactor());

    if (!m_font) {
        std::cerr << "cannot load font: " << fontFileName << std::endl
                  << "error message: " << TTF_GetError() << std::endl;
        throw std::invalid_argument { "cannot load font '" + fontFileName
            + "'. Error message: " + TTF_GetError() };
    }
    m_rendertarget = wptr;
}

void Text::setText(std::string const& text)
{
    m_text = text;
    recreateTextTexture(getRenderTarget());
}
std::string Text::getText() const { return m_text; }

void Text::setOutline(float /*thickness*/, jt::Color /*col*/)
{
    std::cerr << "Font outline not suppored by SDL TTF fonts" << std::endl;
}

void Text::setPosition(jt::Vector2 const& pos) { m_position = pos; }
const jt::Vector2 Text::getPosition() const { return m_position; }

void Text::setColor(const jt::Color& col) { m_color = col; }
const jt::Color Text::getColor() const { return m_color; }

void Text::setFlashColor(const jt::Color& col) { m_flashColor = col; }
const jt::Color Text::getFlashColor() const { return m_flashColor; }

// sf::Transform const getTransform() const  { return m_text->getTransform(); }

jt::Rect const Text::getGlobalBounds() const
{
    return jt::Rect { m_position.x(), m_position.y(), m_textTextureSizeX * m_scale.x(),
        m_textTextureSizeY * m_scale.y() };
}
jt::Rect const Text::getLocalBounds() const
{
    return jt::Rect { 0, 0, m_textTextureSizeX * m_scale.x(), m_textTextureSizeY * m_scale.y() };
}

void Text::setScale(jt::Vector2 const& scale) { m_scale = scale; }
const jt::Vector2 Text::getScale() const { return m_scale; }

void Text::setOrigin(jt::Vector2 const& origin) { m_origin = origin; }
jt::Vector2 const Text::getOrigin() const { return m_origin; }

void Text::SetTextAlign(Text::TextAlign ta)
{
    if (m_textAlign != ta) {
        m_textAlign = ta;
        recreateTextTexture(getRenderTarget());
    }
}
Text::TextAlign Text::getTextAlign() const { return m_textAlign; }

void Text::doUpdate(float /*elapsed*/)
{
    // Nothing to do here
}

void Text::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    auto const destRect = getDestRect(getShadowOffset());
    SDL_Point const p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };

    auto const flip = jt::getFlipFromScale(m_scale);
    auto col = getShadowColor();
    col.a() = std::min(col.a(), m_color.a());
    setSDLColor(col);
    SDL_RenderCopyEx(sptr.get(), m_textTexture.get(), nullptr, &destRect, -getRotation(), &p, flip);
    // std::cout << "error message: " << SDL_GetError() << std::endl;
}

void Text::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    auto const destRect = getDestRect();
    SDL_Point const p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };

    auto const flip = jt::getFlipFromScale(m_scale);
    setSDLColor(getColor());
    SDL_RenderCopyEx(sptr.get(), m_textTexture.get(), nullptr, &destRect, -getRotation(), &p, flip);
    // std::cout << "error message: " << SDL_GetError() << std::endl;
}

void Text::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    auto const destRect = getDestRect();
    SDL_Point const p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };

    auto const flip = jt::getFlipFromScale(m_scale);
    setSDLColor(getFlashColor());
    SDL_RenderCopyEx(sptr.get(), m_textTexture.get(), nullptr, &destRect, -getRotation(), &p, flip);
    // std::cout << "error message: " << SDL_GetError() << std::endl;
}

void Text::doRotate(float /*rot*/)
{
    // Nothing to do here
}

void Text::renderOneLineOfText(std::shared_ptr<jt::renderTarget> const sptr, std::string text,
    std::size_t i, std::size_t lineCount) const
{
    // render text on full white, so coloring can be done afterwards
    SDL_Color const col { 255U, 255U, 255U, 255U };
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, text.c_str(), col);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
        sptr.get(), textSurface); // now you can convert it into a texture

    int w { 0 };
    int h { 0 };
    SDL_QueryTexture(textTexture, NULL, NULL, &w, &h); // get the width and height of the texture

    jt::Vector2 alignOffset {};
    if (lineCount != 0 && m_textAlign == TextAlign::CENTER) {
        alignOffset.x()
            = static_cast<float>(m_textTextureSizeX) / 2.0f - static_cast<float>(w) / 2.0f;
    }
    jt::Vector2 const pos = jt::Vector2 { 0, static_cast<float>(h * i) } + alignOffset;

    SDL_Rect destRect; // create a rect
    destRect.x = pos.x(); // controls the rect's x coordinate
    destRect.y = pos.y(); // controls the rect's y coordinte
    destRect.w = static_cast<int>(w); // controls the width of the rect
    destRect.h = static_cast<int>(h); // controls the height of the rect

    SDL_RenderCopy(sptr.get(), textTexture, nullptr, &destRect);
    // std::cout << "error message: " << SDL_GetError() << std::endl;

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

jt::Vector2u Text::getSizeForLine(
    std::shared_ptr<jt::renderTarget> const sptr, std::string const& text) const
{
    SDL_Color const col { 255U, 255U, 255U, 255U };
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, text.c_str(), col);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
        sptr.get(), textSurface); // now you can convert it into a texture
    int w { 0 };
    int h { 0 };
    SDL_QueryTexture(textTexture, NULL, NULL, &w, &h); // get the width and height of the texture
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    return jt::Vector2u { static_cast<unsigned int>(w), static_cast<unsigned int>(h) };
}

void Text::recreateTextTexture(std::shared_ptr<jt::renderTarget> const sptr)
{
    if (!m_font) {
        std::cout << "no font loaded\n";
        return;
    }
    if (m_text.empty()) {
        std::cout << "no text set loaded\n";
        return;
    }
    if (!sptr) {
        std::cout << "no valid render target in recreateTextTexture" << std::endl;
        return;
    }
    jt::SplitString ss { m_text };
    auto const ssv = ss.split('\n');
    calculateTextTextureSize(sptr, ssv);

    auto oldT = SDL_GetRenderTarget(sptr.get());
    // std::cout << oldT << std::endl;
    m_textTexture = std::shared_ptr<SDL_Texture>(
        SDL_CreateTexture(sptr.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
            m_textTextureSizeX * getUpscaleFactor(), m_textTextureSizeY * getUpscaleFactor()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });

    SDL_SetTextureBlendMode(m_textTexture.get(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(sptr.get(), m_textTexture.get());
    // fill m_textTexture with transparent color, before rendering any text.
    SDL_SetRenderDrawColor(sptr.get(), 0, 0, 0, 0);
    SDL_RenderFillRect(sptr.get(), NULL);

    // draw text line by line
    for (std::size_t i = 0; i != ssv.size(); ++i) {
        renderOneLineOfText(sptr, ssv.at(i), i, ssv.size());
    }
    // reset the renderer to the old texture
    SDL_SetRenderTarget(sptr.get(), oldT);

    // std::cout << "text successfully created\n";
}

std::shared_ptr<jt::renderTarget> Text::getRenderTarget()
{
    if (m_rendertarget.expired()) {
        std::cout << "Cannot use Text without valid renderTarget\n";
        return nullptr;
    }
    return m_rendertarget.lock();
}

void Text::setSDLColor(jt::Color const& col) const
{
    SDL_SetTextureColorMod(m_textTexture.get(), col.r(), col.g(), col.b());
    SDL_SetTextureAlphaMod(m_textTexture.get(), col.a());
}

SDL_Rect Text::getDestRect(jt::Vector2 const& positionOffset) const
{
    jt::Vector2 alignOffset { 0, 0 };
    if (m_textAlign == TextAlign::CENTER) {
        alignOffset.x()
            = -static_cast<float>(m_textTextureSizeX) / 2.0f / getUpscaleFactor() * m_scale.x();
    }

    jt::Vector2 pos = m_position + getShakeOffset() + getOffset() + getCamOffset() + alignOffset
        + positionOffset;

    SDL_Rect destRect; // create a rect
    destRect.x = pos.x(); // controls the rect's x coordinate
    destRect.y = pos.y(); // controls the rect's y coordinte
    destRect.w
        = static_cast<int>(m_textTextureSizeX * m_scale.x()); // controls the width of the rect
    destRect.h
        = static_cast<int>(m_textTextureSizeY * m_scale.y()); // controls the height of the rect

    return destRect;
}

void Text::calculateTextTextureSize(
    std::shared_ptr<jt::renderTarget> const sptr, std::vector<std::string> const& ssv)
{
    unsigned int maxLineLengthInPixel { 0U };
    std::size_t maxLineLengthInChars { 0U };
    for (auto const& l : ssv) {
        if (l.size() > maxLineLengthInChars) {
            maxLineLengthInPixel = getSizeForLine(sptr, l).x();
            maxLineLengthInChars = l.size();
        }
    }

    m_textTextureSizeX = maxLineLengthInPixel;
    m_textTextureSizeY = (ssv.size()) * TTF_FontHeight(m_font);
}

} // namespace jt
