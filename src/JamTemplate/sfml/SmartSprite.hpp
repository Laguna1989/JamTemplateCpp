#ifndef GUARD_JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD

#include "SmartDrawable.hpp"
#include "TextureManager.hpp"
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

    void loadSprite(std::string const& fileName, jt::recti const& rect)
    {
        m_sprite = sf::Sprite { TextureManager::get(fileName), rect };
        m_flashSprite
            = sf::Sprite { TextureManager::get(TextureManager::getFlashName(fileName)), rect };
    }

    void setPosition(jt::vector2 const& pos) override { m_position = pos; }

    const jt::vector2 getPosition() const override { return m_position; }

    void setColor(jt::color const& col) override { m_sprite.setColor(col); }
    const jt::color getColor() const override { return m_sprite.getColor(); }

    void setFlashColor(jt::color const& col) override { m_flashSprite.setColor(col); }
    const jt::color getFlashColor() const override { return m_flashSprite.getColor(); }

    // virtual sf::Transform const getTransform() const override { return m_sprite.getTransform(); }

    virtual jt::rect const getGlobalBounds() const override { return m_sprite.getGlobalBounds(); }
    virtual jt::rect const getLocalBounds() const override { return m_sprite.getLocalBounds(); }

    virtual void setScale(jt::vector2 const& scale)
    {
        m_sprite.setScale(scale);
        m_flashSprite.setScale(scale);
    }

    virtual const jt::vector2 getScale() const { return m_sprite.getScale(); }

    virtual void setOrigin(jt::vector2 const& origin)
    {
        m_sprite.setOrigin(origin);
        m_flashSprite.setOrigin(origin);
    }

    virtual jt::vector2 const getOrigin() const { return m_sprite.getOrigin(); }

private:
    mutable sf::Sprite m_sprite;
    sf::Sprite m_flashSprite;

    jt::vector2 m_position { 0, 0 };

    void doUpdate(float /*elapsed*/) override
    {
        auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset();
        m_sprite.setPosition(pos);
        m_flashSprite.setPosition(pos);
    }

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        jt::vector2 const oldPos = m_sprite.getPosition();
        jt::color const oldCol = m_sprite.getColor();

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
