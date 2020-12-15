#ifndef GUARD_JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD

#include "SmartDrawable.hpp"
#include "TextureManager.hpp"
#include "color.hpp"
#include "rendertarget.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace jt {

class SmartSprite : public SmartDrawable {
public:
    using Sptr = std::shared_ptr<SmartSprite>;

    void loadSprite(std::string const& fileName)
    {
        m_sprite = sf::Sprite { TextureManager::get(fileName) };
        m_flashSprite = sf::Sprite { TextureManager::get(TextureManager::getFlashName(fileName)) };
    }

    void loadSprite(std::string const& fileName, jt::Recti const& rect)
    {
        m_sprite = sf::Sprite { TextureManager::get(fileName), rect };
        m_flashSprite
            = sf::Sprite { TextureManager::get(TextureManager::getFlashName(fileName)), rect };
    }

    void setPosition(jt::Vector2 const& pos) override { m_position = pos; }

    const jt::Vector2 getPosition() const override { return m_position; }

    void setColor(jt::Color const& col) override { m_sprite.setColor(col); }
    const jt::Color getColor() const override { return m_sprite.getColor(); }

    void setFlashColor(jt::Color const& col) override { m_flashSprite.setColor(col); }
    const jt::Color getFlashColor() const override { return m_flashSprite.getColor(); }

    // virtual sf::Transform const getTransform() const override { return m_sprite.getTransform(); }

    virtual jt::Rect const getGlobalBounds() const override { return m_sprite.getGlobalBounds(); }
    virtual jt::Rect const getLocalBounds() const override { return m_sprite.getLocalBounds(); }

    virtual void setScale(jt::Vector2 const& scale)
    {
        m_sprite.setScale(scale);
        m_flashSprite.setScale(scale);
    }

    virtual const jt::Vector2 getScale() const { return m_sprite.getScale(); }

    virtual void setOrigin(jt::Vector2 const& origin)
    {
        m_sprite.setOrigin(origin);
        m_flashSprite.setOrigin(origin);
    }

    virtual jt::Vector2 const getOrigin() const { return m_sprite.getOrigin(); }

    // WARNING: This function is slow, because it needs to copy
    // graphics memory to ram first.
    jt::Color getColorAtPixel(jt::Vector2u pixelPos) const
    {
        // optimization to avoid unneccesary copies
        if (!m_imageStored) {
            m_imageStored = true;
            m_image = m_sprite.getTexture()->copyToImage();
        }
        return jt::Color { m_image.getPixel(pixelPos.x(), pixelPos.y()) };
    }

    void cleanImage()
    {
        m_imageStored = false;
        m_image = sf::Image {};
    }

private:
    mutable sf::Sprite m_sprite;
    sf::Sprite m_flashSprite;
    // optimization for getColorAtPixel
    mutable sf::Image m_image;
    mutable bool m_imageStored { false };

    jt::Vector2 m_position { 0, 0 };

    void doUpdate(float /*elapsed*/) override
    {
        auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset();
        m_sprite.setPosition(pos);
        m_flashSprite.setPosition(pos);
    }

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        jt::Vector2 const oldPos = m_sprite.getPosition();
        jt::Color const oldCol = m_sprite.getColor();

        m_sprite.setPosition(oldPos + getShadowOffset());
        m_sprite.setColor(getShadowColor());
        sptr->draw(m_sprite);

        m_sprite.setPosition(oldPos);
        m_sprite.setColor(oldCol);
    }

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        sptr->draw(m_sprite);
    }

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        sptr->draw(m_flashSprite);
    }

    void doRotate(float rot)
    {
        m_sprite.setRotation(-rot);
        m_flashSprite.setRotation(-rot);
    }
};

} // namespace jt

#endif
