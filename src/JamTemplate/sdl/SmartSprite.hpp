#ifndef JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD

#include "MathHelper.hpp"
#include "SmartObject.hpp"
#include "TextureManager.hpp"
#include "rendertarget.hpp"
#include <SDL.h>
#include <memory>
#include <string>

namespace JamTemplate {

class SmartSprite : public SmartObject {
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

        // TODO FlashSprite
    }

    void loadSprite(std::string const& fileName, jt::recti const& rect)
    {
        m_text = TextureManager::get(fileName);
        int w { 0 };
        int h { 0 };
        SDL_QueryTexture(
            m_text.get(), NULL, NULL, &w, &h); // get the width and height of the texture
        m_sourceRect = jt::recti { rect };

        // TODO FlashSprite
    }

    void setPosition(jt::vector2 const& pos) override { m_position = pos; }

    const jt::vector2 getPosition() const override { return m_position; }

    void setColor(jt::color const& col) override { m_color = col; }
    const jt::color getColor() const override { return m_color; }

    void setFlashColor(jt::color const& col) override
    { /*m_flashSprite.setColor(col);*/
    }
    const jt::color getFlashColor() const override
    {
        return jt::colors::White; /*return m_flashSprite.getColor();*/
    }

    // virtual sf::Transform const getTransform() const override { return m_sprite.getTransform(); }

    virtual jt::rect const getGlobalBounds() const override { return jt::rect {}; }
    virtual jt::rect const getLocalBounds() const override { return jt::rect {}; }

    virtual void setScale(jt::vector2 const& scale) override { m_scale = scale; }

    virtual const jt::vector2 getScale() const override { return m_scale; }

    virtual void setOrigin(jt::vector2 const& origin) override
    {
        // TODO
        // m_sprite.setOrigin(origin);
        // m_flashSprite.setOrigin(origin);
    }

    virtual jt::vector2 const getOrigin() const override
    {
        // TODO
        return jt::vector2 {};
    }

private:
    mutable std::shared_ptr<SDL_Texture> m_text;

    jt::vector2 m_position { 0, 0 };
    jt::recti m_sourceRect { 0, 0, 0, 0 };
    jt::color m_color;
    jt::vector2 m_scale { 1.0f, 1.0f };
    float m_angle { 0.0f };

    void doUpdate(float /*elapsed*/) override
    {

        // m_flashSprite.setPosition(pos);
    }

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        // TODO
        // jt::vector2 const oldPos = m_sprite.getPosition();
        // jt::color const oldCol = m_sprite.getColor();

        // m_sprite.setPosition(oldPos + getShadowOffset());
        // m_sprite.setColor(getShadowColor());
        // sptr->draw(m_sprite);

        // m_sprite.setPosition(oldPos);
        // m_sprite.setColor(oldCol);
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

        SDL_RenderCopyEx(sptr.get(), m_text.get(), &sourceRect, &destRect, m_angle, nullptr, flip);
    }

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        // sptr->draw(m_flashSprite);
    }

    void doRotate(float /*rot*/) override
    {
        // TODO
        // m_sprite.setRotation(-rot);
        // m_flashSprite.setRotation(-rot);
    }
}; // namespace JamTemplate

} // namespace JamTemplate

#endif
