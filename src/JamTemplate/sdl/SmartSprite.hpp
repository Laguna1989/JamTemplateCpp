#ifndef JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD

#include "MathHelper.hpp"
#include "SmartDrawable.hpp"
#include "TextureManager.hpp"
#include "rendertarget.hpp"
#include <SDL.h>
#include <memory>
#include <string>

namespace jt {

class SmartSprite : public SmartDrawable {
public:
    using Sptr = std::shared_ptr<SmartSprite>;

    void loadSprite(std::string const& fileName)
    {
        m_text = TextureManager::get(fileName);
        int w { 0 };
        int h { 0 };
        SDL_QueryTexture(
            m_text.get(), NULL, NULL, &w, &h); // get the width and height of the texture
        m_sourceRect = jt::recti { 0, 0, w, h };

        m_textFlash = TextureManager::get(TextureManager::getFlashName(fileName));
    }

    void loadSprite(std::string const& fileName, jt::recti const& rect)
    {
        m_text = TextureManager::get(fileName);
        int w { 0 };
        int h { 0 };
        SDL_QueryTexture(
            m_text.get(), NULL, NULL, &w, &h); // get the width and height of the texture
        m_sourceRect = jt::recti { rect };

        m_textFlash = TextureManager::get(TextureManager::getFlashName(fileName));
    }

    void setPosition(jt::vector2 const& pos) override { m_position = pos; }

    const jt::vector2 getPosition() const override { return m_position; }

    void setColor(jt::color const& col) override { m_color = col; }
    const jt::color getColor() const override { return m_color; }

    void setFlashColor(jt::color const& col) override { m_colorFlash = col; }
    const jt::color getFlashColor() const override { return m_colorFlash; }

    // virtual sf::Transform const getTransform() const override { return m_sprite.getTransform(); }

    virtual jt::rect const getGlobalBounds() const override { return jt::rect {}; }
    virtual jt::rect const getLocalBounds() const override { return jt::rect {}; }

    virtual void setScale(jt::vector2 const& scale) override { m_scale = scale; }

    virtual const jt::vector2 getScale() const override { return m_scale; }

    virtual void setOrigin(jt::vector2 const& origin) override { m_origin = origin; }

    virtual jt::vector2 const getOrigin() const override { return m_origin; }

private:
    mutable std::shared_ptr<SDL_Texture> m_text;

    jt::vector2 m_position { 0, 0 };
    jt::recti m_sourceRect { 0, 0, 0, 0 };
    jt::color m_color { jt::colors::White };
    jt::vector2 m_scale { 1.0f, 1.0f };
    jt::vector2 m_origin { 0.0f, 0.0f };

    mutable std::shared_ptr<SDL_Texture> m_textFlash;
    jt::color m_colorFlash { jt::colors::White };

    void doUpdate(float /*elapsed*/) override
    {

        // m_flashSprite.setPosition(pos);
    }

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset();
        SDL_Rect sourceRect { m_sourceRect.left(), m_sourceRect.top(), m_sourceRect.width(),
            m_sourceRect.height() };
        float scalex = fabs(m_scale.x());
        float scaley = fabs(m_scale.y());
        auto flip = SDL_FLIP_NONE;
        if (m_scale.x() < 0 && m_scale.y() < 0) {
            flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        } else if (m_scale.x() < 0 && m_scale.y() >= 0) {
            flip = SDL_FLIP_HORIZONTAL;
        } else if (m_scale.x() >= 0 && m_scale.y() < 0) {
            flip = SDL_FLIP_VERTICAL;
        }
        SDL_Rect destRect { static_cast<int>(pos.x()), static_cast<int>(pos.y()),
            static_cast<int>(m_sourceRect.width() * scalex),
            static_cast<int>(m_sourceRect.height() * scaley) };
        SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
        SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
        SDL_SetTextureColorMod(m_text.get(), m_color.r(), m_color.g(), m_color.b());
        SDL_SetTextureAlphaMod(m_text.get(), m_color.a());
        SDL_RenderCopyEx(sptr.get(), m_text.get(), &sourceRect, &destRect, getRotation(), &p, flip);
    }

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        auto const pos
            = m_position + getShakeOffset() + getOffset() + getCamOffset() + getShadowOffset();
        SDL_Rect sourceRect { m_sourceRect.left(), m_sourceRect.top(), m_sourceRect.width(),
            m_sourceRect.height() };
        float scalex = fabs(m_scale.x());
        float scaley = fabs(m_scale.y());
        auto flip = SDL_FLIP_NONE;
        if (m_scale.x() < 0 && m_scale.y() < 0) {
            flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        } else if (m_scale.x() < 0 && m_scale.y() >= 0) {
            flip = SDL_FLIP_HORIZONTAL;
        } else if (m_scale.x() >= 0 && m_scale.y() < 0) {
            flip = SDL_FLIP_VERTICAL;
        }
        SDL_Rect destRect { static_cast<int>(pos.x()), static_cast<int>(pos.y()),
            static_cast<int>(m_sourceRect.width() * scalex),
            static_cast<int>(m_sourceRect.height() * scaley) };
        SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
        SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
        SDL_SetTextureColorMod(
            m_text.get(), getShadowColor().r(), getShadowColor().g(), getShadowColor().b());
        SDL_SetTextureAlphaMod(m_text.get(), getShadowColor().a());
        SDL_RenderCopyEx(sptr.get(), m_text.get(), &sourceRect, &destRect, getRotation(), &p, flip);
    }

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset();
        SDL_Rect sourceRect { m_sourceRect.left(), m_sourceRect.top(), m_sourceRect.width(),
            m_sourceRect.height() };
        float scalex = fabs(m_scale.x());
        float scaley = fabs(m_scale.y());
        auto flip = SDL_FLIP_NONE;
        if (m_scale.x() < 0 && m_scale.y() < 0) {
            flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        } else if (m_scale.x() < 0 && m_scale.y() >= 0) {
            flip = SDL_FLIP_HORIZONTAL;
        } else if (m_scale.x() >= 0 && m_scale.y() < 0) {
            flip = SDL_FLIP_VERTICAL;
        }
        SDL_Rect destRect { static_cast<int>(pos.x()), static_cast<int>(pos.y()),
            static_cast<int>(m_sourceRect.width() * scalex),
            static_cast<int>(m_sourceRect.height() * scaley) };
        SDL_Point p { static_cast<int>(m_origin.x()), static_cast<int>(m_origin.y()) };
        SDL_SetRenderDrawBlendMode(sptr.get(), SDL_BLENDMODE_BLEND);
        SDL_SetTextureColorMod(
            m_textFlash.get(), getFlashColor().r(), getFlashColor().g(), getFlashColor().b());
        SDL_SetTextureAlphaMod(m_textFlash.get(), getFlashColor().a());
        SDL_RenderCopyEx(
            sptr.get(), m_textFlash.get(), &sourceRect, &destRect, getRotation(), &p, flip);
    }

    void doRotate(float /*rot*/) override { }
}; // namespace jt

} // namespace jt

#endif
