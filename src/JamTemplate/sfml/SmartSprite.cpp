#include "SmartSprite.hpp"
#include "TextureManager.hpp"

namespace jt {

void SmartSprite::loadSprite(std::string const& fileName)
{
    m_sprite = sf::Sprite { TextureManager::get(fileName) };
    m_flashSprite = sf::Sprite { TextureManager::get(TextureManager::getFlashName(fileName)) };
}

void SmartSprite::loadSprite(std::string const& fileName, jt::Recti const& rect)
{
    m_sprite = sf::Sprite { TextureManager::get(fileName), rect };
    m_flashSprite
        = sf::Sprite { TextureManager::get(TextureManager::getFlashName(fileName)), rect };
}

void SmartSprite::setPosition(jt::Vector2 const& pos) { m_position = pos; }
const jt::Vector2 SmartSprite::getPosition() const { return m_position; }

void SmartSprite::setColor(jt::Color const& col) { m_sprite.setColor(col); }
const jt::Color SmartSprite::getColor() const { return m_sprite.getColor(); }

void SmartSprite::setFlashColor(jt::Color const& col) { m_flashSprite.setColor(col); }
const jt::Color SmartSprite::getFlashColor() const { return m_flashSprite.getColor(); }

jt::Rect const SmartSprite::getGlobalBounds() const { return m_sprite.getGlobalBounds(); }
jt::Rect const SmartSprite::getLocalBounds() const { return m_sprite.getLocalBounds(); }

void SmartSprite::setScale(jt::Vector2 const& scale)
{
    m_sprite.setScale(scale);
    m_flashSprite.setScale(scale);
}

const jt::Vector2 SmartSprite::getScale() const { return m_sprite.getScale(); }

void SmartSprite::setOrigin(jt::Vector2 const& origin)
{
    m_sprite.setOrigin(origin);
    m_flashSprite.setOrigin(origin);
}

jt::Vector2 const SmartSprite::getOrigin() const { return m_sprite.getOrigin(); }

// WARNING: This function is slow, because it needs to copy
// graphics memory to ram first.
jt::Color SmartSprite::getColorAtPixel(jt::Vector2u pixelPos) const
{
    // optimization to avoid unneccesary copies
    if (!m_imageStored) {
        m_imageStored = true;
        m_image = m_sprite.getTexture()->copyToImage();
    }
    return jt::Color { m_image.getPixel(pixelPos.x(), pixelPos.y()) };
}

void SmartSprite::cleanImage()
{
    m_imageStored = false;
    m_image = sf::Image {};
}

void SmartSprite::doUpdate(float /*elapsed*/)
{
    // std::cout << "SmartSprite.CamOffset.x " << getCamOffset().x() << std::endl;
    auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset();
    // std::cout << "SmartSprite.final position.x " << pos.x() << std::endl;
    m_sprite.setPosition(pos);
    m_flashSprite.setPosition(pos);
}

void SmartSprite::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    jt::Vector2 const oldPos = m_sprite.getPosition();
    jt::Color const oldCol = m_sprite.getColor();

    m_sprite.setPosition(oldPos + getShadowOffset());
    m_sprite.setColor(getShadowColor());
    sptr->draw(m_sprite);

    m_sprite.setPosition(oldPos);
    m_sprite.setColor(oldCol);
}

void SmartSprite::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    sptr->draw(m_sprite);
}

void SmartSprite::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    sptr->draw(m_flashSprite);
}

void SmartSprite::doRotate(float rot)
{
    m_sprite.setRotation(-rot);
    m_flashSprite.setRotation(-rot);
}

} // namespace jt
