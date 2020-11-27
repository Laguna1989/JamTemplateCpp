#ifndef JAMTEMPLATE_SMARTTEXT_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTTEXT_HPP_INCLUDEGUARD

#include "SmartObject.hpp"
#include "rendertarget.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <exception>
#include <memory>
#include <string>

namespace JamTemplate {

class SmartText : public SmartObject {
public:
    enum class TextAlign { CENTER, LEFT, RIGHT };

    using Sptr = std::shared_ptr<SmartText>;

    virtual ~SmartText() { m_font = nullptr; }

    void loadFont(std::string const& fontFileName, unsigned int characterSize)
    {
        m_font = TTF_OpenFont(fontFileName.c_str(), characterSize);

        if (!m_font) {
            std::cerr << "cannot load font: " << fontFileName << std::endl
                      << "error message: " << TTF_GetError() << std::endl;
            return;
        }
    }

    void setText(std::string const& text) { m_text = text; }
    std::string getText() const { return m_text; }

    void setOutline(float /*thickness*/, jt::color /*col*/)
    {
        // m_text->setOutlineThickness(thickness);
        // m_text->setOutlineColor(col);
    }

    void setPosition(jt::vector2 const& pos) override { m_position = pos; }

    const jt::vector2 getPosition() const override { return m_position; }

    void setColor(const jt::color& col) override { m_color = col; }
    const jt::color getColor() const override { return m_color; }

    void setFlashColor(const jt::color& col) override { m_flashColor = col; }
    const jt::color getFlashColor() const override { return m_flashColor; }

    // virtual sf::Transform const getTransform() const override { return m_text->getTransform(); }

    jt::rect const getGlobalBounds() const override
    {
        // TODO
        return jt::rect {};
    }
    jt::rect const getLocalBounds() const override
    {
        // TODO
        return jt::rect {};
    }

    virtual void setScale(jt::vector2 const& scale) override { m_scale = scale; }

    virtual const jt::vector2 getScale() const override { return m_scale; }

    virtual void setOrigin(jt::vector2 const& origin) override { m_origin = origin; }

    virtual jt::vector2 const getOrigin() const override { return m_origin; }

    void SetTextAlign(TextAlign ta) { m_textAlign = ta; }
    TextAlign getTextAlign() const { return m_textAlign; }

private:
    TTF_Font* m_font;
    std::string m_text;

    TextAlign m_textAlign { TextAlign::CENTER };

    jt::vector2 m_position { 0, 0 };
    jt::color m_color { jt::colors::White };
    jt::color m_flashColor;
    jt::vector2 m_origin { 0.0f, 0.0f };
    jt::vector2 m_scale { 1.0f, 1.0f };

    void doUpdate(float /*elapsed*/) override { }

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        SDL_Color col { getShadowColor().r(), getShadowColor().g(), getShadowColor().b(),
            getShadowColor().a() };

        SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), col);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
            sptr.get(), textSurface); // now you can convert it into a texture
        int w { 0 };
        int h { 0 };
        SDL_QueryTexture(
            textTexture, NULL, NULL, &w, &h); // get the width and height of the texture

        jt::vector2 alignOffset {};
        if (m_textAlign != TextAlign::LEFT) {
            alignOffset.x() = w / (m_textAlign == TextAlign::CENTER ? 2.0f : 1.0f);
        }
        jt::vector2 pos = m_position + getShakeOffset() + getOffset() - alignOffset + getCamOffset()
            + getShadowOffset();

        SDL_Rect Message_rect; // create a rect
        Message_rect.x = pos.x(); // controls the rect's x coordinate
        Message_rect.y = pos.y(); // controls the rect's y coordinte
        Message_rect.w = static_cast<int>(w * m_scale.x()); // controls the width of the rect
        Message_rect.h = static_cast<int>(h * m_scale.y()); // controls the height of the rect

        SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };

        auto flip = SDL_FLIP_NONE;
        if (m_scale.x() < 0 && m_scale.y() < 0) {
            flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        } else if (m_scale.x() < 0 && m_scale.y() >= 0) {
            flip = SDL_FLIP_HORIZONTAL;
        } else if (m_scale.x() >= 0 && m_scale.y() < 0) {
            flip = SDL_FLIP_VERTICAL;
        }

        SDL_RenderCopyEx(sptr.get(), textTexture, nullptr, &Message_rect, getRotation(), &p, flip);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    void drawOneLine(std::shared_ptr<jt::renderTarget> const sptr) const
    {
        // draw text line here
        SDL_Color col { m_color.r(), m_color.g(), m_color.b(), m_color.a() };

        SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), col);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
            sptr.get(), textSurface); // now you can convert it into a texture
        int w { 0 };
        int h { 0 };
        SDL_QueryTexture(
            textTexture, NULL, NULL, &w, &h); // get the width and height of the texture

        jt::vector2 alignOffset {};
        if (m_textAlign != TextAlign::LEFT) {
            alignOffset.x() = w / (m_textAlign == TextAlign::CENTER ? 2.0f : 1.0f);
        }
        jt::vector2 pos
            = m_position + getShakeOffset() + getOffset() - alignOffset + getCamOffset();

        SDL_Rect Message_rect; // create a rect
        Message_rect.x = pos.x(); // controls the rect's x coordinate
        Message_rect.y = pos.y(); // controls the rect's y coordinte
        Message_rect.w = static_cast<int>(w * m_scale.x()); // controls the width of the rect
        Message_rect.h = static_cast<int>(h * m_scale.y()); // controls the height of the rect

        SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };

        auto flip = SDL_FLIP_NONE;
        if (m_scale.x() < 0 && m_scale.y() < 0) {
            flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        } else if (m_scale.x() < 0 && m_scale.y() >= 0) {
            flip = SDL_FLIP_HORIZONTAL;
        } else if (m_scale.x() >= 0 && m_scale.y() < 0) {
            flip = SDL_FLIP_VERTICAL;
        }

        SDL_RenderCopyEx(sptr.get(), textTexture, nullptr, &Message_rect, getRotation(), &p, flip);
        // std::cout << "error message: " << SDL_GetError() << std::endl;

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        auto oldT = SDL_GetRenderTarget(sptr.get());
        // // // std::cout << oldT << std::endl;
        SDL_Texture* tempT = SDL_CreateTexture(
            sptr.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 400, 300);

        SDL_SetTextureBlendMode(tempT, SDL_BLENDMODE_BLEND);
        SDL_SetRenderTarget(sptr.get(), tempT);
        SDL_RenderClear(sptr.get());

        // draw one line
        drawOneLine(sptr);

        // set the old texture
        SDL_SetRenderTarget(sptr.get(), oldT);
        // draw new texture on old texture
        SDL_RenderCopyEx(sptr.get(), tempT, nullptr, nullptr, 0.0f, nullptr, SDL_FLIP_NONE);
        SDL_DestroyTexture(tempT);
    }

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const /*sptr*/) const override
    {
        // TODO
    }

    void doRotate(float /*rot*/) override { }
};
} // namespace JamTemplate

#endif
