#ifndef JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "SmartObject.hpp"
#include "TextureManager.hpp"

namespace JamTemplate {

class SmartSprite : public SmartObject {
public:
    using Sptr = std::shared_ptr<SmartSprite>;

    void loadSprite(std::string const& fileName)
    {
        m_sprite = sf::Sprite { TextureManager::get(fileName) };
        m_flashSprite = sf::Sprite { TextureManager::get(TextureManager::getFlashName(fileName)) };
    }

    void loadSprite(std::string const& fileName, sf::IntRect const& rect)
    {
        m_sprite = sf::Sprite { TextureManager::get(fileName), rect };
        m_flashSprite
            = sf::Sprite { TextureManager::get(TextureManager::getFlashName(fileName)), rect };
    }

    void setPosition(sf::Vector2f const& pos) override { m_position = pos; }

    const sf::Vector2f getPosition() const override { return m_position; }

    void setColor(sf::Color const& col) override { m_sprite.setColor(col); }
    const sf::Color getColor() const override { return m_sprite.getColor(); }

    void setFlashColor(sf::Color const& col) override { m_flashSprite.setColor(col); }
    const sf::Color getFlashColor() const override { return m_flashSprite.getColor(); }

    virtual sf::Transform const getTransform() const override { return m_sprite.getTransform(); }

    virtual sf::FloatRect const getGlobalBounds() const override
    {
        return m_sprite.getGlobalBounds();
    }
    virtual sf::FloatRect const getLocalBounds() const override
    {
        return m_sprite.getLocalBounds();
    }

    virtual void setScale(sf::Vector2f const& scale)
    {
        m_sprite.setScale(scale);
        m_flashSprite.setScale(scale);
    }

    virtual const sf::Vector2f getScale() const { return m_sprite.getScale(); }

    virtual void setOrigin(sf::Vector2f const& origin)
    {
        m_sprite.setOrigin(origin);
        m_flashSprite.setOrigin(origin);
    }

    virtual sf::Vector2f const getOrigin() const { return m_sprite.getOrigin(); }

private:
    mutable sf::Sprite m_sprite;
    sf::Sprite m_flashSprite;

    sf::Vector2f m_position { 0, 0 };

    void doUpdate(float /*elapsed*/) override
    {
        auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset();
        m_sprite.setPosition(pos);
        m_flashSprite.setPosition(pos);
    }

    void doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const override
    {
        sf::Vector2f const oldPos = m_sprite.getPosition();
        sf::Color const oldCol = m_sprite.getColor();

        m_sprite.setPosition(oldPos + getShadowOffset());
        m_sprite.setColor(getShadowColor());
        sptr->draw(m_sprite);

        m_sprite.setPosition(oldPos);
        m_sprite.setColor(oldCol);
    }

    void doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const override
    {
        sptr->draw(m_sprite);
    }

    void doDrawFlash(std::shared_ptr<sf::RenderTarget> const sptr) const override
    {
        sptr->draw(m_flashSprite);
    }

    void doRotate(float rot)
    {
        m_sprite.setRotation(-rot);
        m_flashSprite.setRotation(-rot);
    }
};

} // namespace JamTemplate

#endif
