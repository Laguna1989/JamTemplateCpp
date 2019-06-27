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

    void loadSprite(std::string fileName)
    {
        m_sprite = sf::Sprite { TextureManager::get(fileName) };
        m_flashSprite = sf::Sprite { TextureManager::get(TextureManager::getFlashName(fileName)) };
    }

    void loadSprite(std::string fileName, sf::IntRect rect)
    {
        m_sprite = sf::Sprite { TextureManager::get(fileName), rect };
        m_flashSprite = sf::Sprite { TextureManager::get(TextureManager::getFlashName(fileName)), rect };
    }

    void setPosition(sf::Vector2f const& pos) override
    {
        m_position = pos;
    }

    const sf::Vector2f getPosition() const override
    {
        return m_position;
    }

    void setColor(const sf::Color& col) override
    {
        m_sprite.setColor(col);
    }
    const sf::Color getColor() const override
    {
        return m_sprite.getColor();
    }

    void setFlashColor(const sf::Color& col) override
    {
        m_flashSprite.setColor(col);
    }
    const sf::Color getFlashColor() const override
    {
        return m_flashSprite.getColor();
    }

    virtual sf::Transform const getTransform() const override
    {
        return m_sprite.getTransform();
    }

    virtual sf::FloatRect getGlobalBounds() const override
    {
        return m_sprite.getGlobalBounds();
    }
    virtual sf::FloatRect getLocalBounds() const override
    {
        return m_sprite.getLocalBounds();
    }

    virtual void setScale(sf::Vector2f const& scale)
    {
        m_sprite.setScale(scale);
    }

    virtual const sf::Vector2f getScale() const
    {
        return m_sprite.getScale();
    }

    virtual void setOrigin(sf::Vector2f const& origin)
    {
        m_sprite.setOrigin(origin);
        m_flashSprite.setOrigin(origin);
    }

    virtual const sf::Vector2f getOrigin() const
    {
        return m_sprite.getOrigin();
    }

private:
    sf::Sprite m_sprite;
    sf::Sprite m_flashSprite;

    sf::Vector2f m_position { 0, 0 };

    void doUpdate(float /*elapsed*/) override
    {
        m_sprite.setPosition(m_position + getShakeOffset() + getOffset() + getCamOffset());
        m_flashSprite.setPosition(m_position + getShakeOffset() + getOffset() + getCamOffset());
        m_flashSprite.setScale(m_sprite.getScale());
    }

    void doDraw(std::shared_ptr<sf::RenderTarget> sptr) const override
    {
        sptr->draw(m_sprite);
    }

    void doDrawFlash(std::shared_ptr<sf::RenderTarget> sptr) const override
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
