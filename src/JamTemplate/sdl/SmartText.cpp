
#include "SmartText.hpp"
#include "SplitString.hpp"
#include "rendertarget.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <exception>

namespace JamTemplate {

SmartText::~SmartText()
{
    if (m_font != nullptr) {
        TTF_CloseFont(m_font);
    }
}

void SmartText::loadFont(std::string const& fontFileName, unsigned int characterSize,
    std::weak_ptr<jt::renderTarget> wptr)
{
    m_font = TTF_OpenFont(fontFileName.c_str(), characterSize);

    if (!m_font) {
        std::cerr << "cannot load font: " << fontFileName << std::endl
                  << "error message: " << TTF_GetError() << std::endl;
        return;
    }
    m_characterSize = characterSize;
    m_rendertarget = wptr;
}

void SmartText::setText(std::string const& text)
{
    m_text = text;
    recreateTextTexture(getRenderTarget());
}
std::string SmartText::getText() const { return m_text; }

void SmartText::setOutline(float /*thickness*/, jt::color /*col*/)
{
    // m_text->setOutlineThickness(thickness);
    // m_text->setOutlineColor(col);
}

void SmartText::setPosition(jt::vector2 const& pos) { m_position = pos; }

const jt::vector2 SmartText::getPosition() const { return m_position; }

void SmartText::setColor(const jt::color& col) { m_color = col; }
const jt::color SmartText::getColor() const { return m_color; }

void SmartText::setFlashColor(const jt::color& col) { m_flashColor = col; }
const jt::color SmartText::getFlashColor() const { return m_flashColor; }

// sf::Transform const getTransform() const  { return m_text->getTransform(); }

jt::rect const SmartText::getGlobalBounds() const
{
    // TODO
    return jt::rect {};
}
jt::rect const SmartText::getLocalBounds() const
{
    // TODO
    return jt::rect {};
}

void SmartText::setScale(jt::vector2 const& scale) { m_scale = scale; }
const jt::vector2 SmartText::getScale() const { return m_scale; }

void SmartText::setOrigin(jt::vector2 const& origin) { m_origin = origin; }
jt::vector2 const SmartText::getOrigin() const { return m_origin; }

void SmartText::SetTextAlign(SmartText::TextAlign ta)
{
    if (m_textAlign != ta) {
        m_textAlign = ta;
        recreateTextTexture(getRenderTarget());
    }
}
SmartText::TextAlign SmartText::getTextAlign() const { return m_textAlign; }

void SmartText::doUpdate(float /*elapsed*/) { }

void SmartText::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    SDL_Color col { getShadowColor().r(), getShadowColor().g(), getShadowColor().b(),
        getShadowColor().a() };

    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), col);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
        sptr.get(), textSurface); // now you can convert it into a texture
    int w { 0 };
    int h { 0 };
    SDL_QueryTexture(textTexture, NULL, NULL, &w, &h); // get the width and height of the texture

    jt::vector2 alignOffset {};
    if (m_textAlign != TextAlign::LEFT) {
        alignOffset.x() = w / (m_textAlign == TextAlign::CENTER ? 2.0f : 1.0f);
    }
    jt::vector2 pos = m_position + getShakeOffset() + getOffset() - alignOffset + getCamOffset()
        + getShadowOffset();

    SDL_Rect destRect; // create a rect
    destRect.x = pos.x(); // controls the rect's x coordinate
    destRect.y = pos.y(); // controls the rect's y coordinte
    destRect.w = static_cast<int>(w * m_scale.x()); // controls the width of the rect
    destRect.h = static_cast<int>(h * m_scale.y()); // controls the height of the rect

    SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };

    auto flip = SDL_FLIP_NONE;
    if (m_scale.x() < 0 && m_scale.y() < 0) {
        flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    } else if (m_scale.x() < 0 && m_scale.y() >= 0) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (m_scale.x() >= 0 && m_scale.y() < 0) {
        flip = SDL_FLIP_VERTICAL;
    }

    SDL_RenderCopyEx(sptr.get(), textTexture, nullptr, &destRect, getRotation(), &p, flip);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void SmartText::drawOneLine(std::shared_ptr<jt::renderTarget> const sptr, std::string text,
    std::size_t i, std::size_t lineCount) const
{
    SDL_Color col { 255U, 255U, 255U, 255U };
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, text.c_str(), col);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
        sptr.get(), textSurface); // now you can convert it into a texture

    int w { 0 };
    int h { 0 };
    SDL_QueryTexture(textTexture, NULL, NULL, &w, &h); // get the width and height of the texture

    // std::cout << "FontHeight: " << TTF_FontHeight(m_font) << " TextureHeight: " << h
    //           << std::endl;
    jt::vector2 alignOffset {};
    if (lineCount != 0 && m_textAlign == TextAlign::CENTER) {
        alignOffset.x()
            = static_cast<float>(m_textTextureSizeX) / 2.0f - static_cast<float>(w) / 2.0f;
    }
    // std::cout << "drawOneLine alignOffsetX" << alignOffset.x() << " " << m_textTextureSizeX / 2
    // << "
    // "
    // << w / 2 << std::endl;
    jt::vector2 pos = jt::vector2 { 0, static_cast<float>(h * i) } + alignOffset;

    SDL_Rect destRect; // create a rect
    destRect.x = pos.x(); // controls the rect's x coordinate
    destRect.y = pos.y(); // controls the rect's y coordinte
    destRect.w = static_cast<int>(w); // controls the width of the rect
    destRect.h = static_cast<int>(h); // controls the height of the rect

    SDL_RenderCopyEx(sptr.get(), textTexture, nullptr, &destRect, 0.0f, nullptr, SDL_FLIP_NONE);
    // std::cout << "error message: " << SDL_GetError() << std::endl;

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

jt::vector2u SmartText::getSizeForLine(
    std::shared_ptr<jt::renderTarget> const sptr, std::string const& text) const
{
    SDL_Color col { 255U, 255U, 255U, 255U };
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, text.c_str(), col);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
        sptr.get(), textSurface); // now you can convert it into a texture
    int w { 0 };
    int h { 0 };
    SDL_QueryTexture(textTexture, NULL, NULL, &w, &h); // get the width and height of the texture
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    return jt::vector2u { static_cast<unsigned int>(w), static_cast<unsigned int>(h) };
}

void SmartText::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    jt::vector2 alignOffset { 0, 0 };
    if (m_textAlign == TextAlign::CENTER) {
        alignOffset.x() = -static_cast<float>(m_textTextureSizeX) / 2.0f;
    }

    jt::vector2 pos = m_position + getShakeOffset() + getOffset() + getCamOffset() + alignOffset;

    // std::cout << "draw alignOffsetX " << alignOffset.x() << std::endl;
    SDL_Rect destRect; // create a rect
    destRect.x = pos.x(); // controls the rect's x coordinate
    destRect.y = pos.y(); // controls the rect's y coordinte
    destRect.w
        = static_cast<int>(m_textTextureSizeX * m_scale.x()); // controls the width of the rect
    destRect.h
        = static_cast<int>(m_textTextureSizeY * m_scale.y()); // controls the height of the rect

    SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };

    auto flip = SDL_FLIP_NONE;
    if (m_scale.x() < 0 && m_scale.y() < 0) {
        flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    } else if (m_scale.x() < 0 && m_scale.y() >= 0) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (m_scale.x() >= 0 && m_scale.y() < 0) {
        flip = SDL_FLIP_VERTICAL;
    }

    SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(m_textTexture.get(), m_color.r(), m_color.g(), m_color.b());
    SDL_SetTextureAlphaMod(m_textTexture.get(), m_color.a());

    SDL_RenderCopyEx(sptr.get(), m_textTexture.get(), nullptr, &destRect, -getRotation(), &p, flip);
    // std::cout << "error message: " << SDL_GetError() << std::endl;
}

void SmartText::doDrawFlash(std::shared_ptr<jt::renderTarget> const /*sptr*/) const
{
    // TODO
}

void SmartText::doRotate(float /*rot*/) { }

void SmartText::recreateTextTexture(std::shared_ptr<jt::renderTarget> const sptr)
{
    // std::cout << "recreate Texture" << std::endl;

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
    JamTemplate::SplitString ss { m_text };
    auto const ssv = ss.split('\n');
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

    auto oldT = SDL_GetRenderTarget(sptr.get());
    // // // std::cout << oldT << std::endl;
    m_textTexture = std::shared_ptr<SDL_Texture>(
        SDL_CreateTexture(sptr.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
            m_textTextureSizeX, m_textTextureSizeY),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });

    SDL_SetTextureBlendMode(m_textTexture.get(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(sptr.get(), m_textTexture.get());
    SDL_SetRenderDrawColor(sptr.get(), 0, 0, 0, 0);
    SDL_RenderFillRect(sptr.get(), NULL);

    for (std::size_t i = 0; i != ssv.size(); ++i) {
        auto const text = ssv.at(i);
        // draw one line
        drawOneLine(sptr, text, i, ssv.size());
    }
    // set the old texture
    SDL_SetRenderTarget(sptr.get(), oldT);
    // draw new texture on old texture

    // std::cout << "text successfully created\n";
}

std::shared_ptr<jt::renderTarget> SmartText::getRenderTarget()
{
    if (m_rendertarget.expired()) {
        std::cout << "Cannot use SmartText without valid renderTarget\n";
        return nullptr;
    }
    return m_rendertarget.lock();
}

} // namespace JamTemplate
