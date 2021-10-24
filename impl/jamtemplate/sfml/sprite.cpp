#include "sprite.hpp"
#include "texture_manager.hpp"

namespace jt {

void Sprite::fromTexture(sf::Texture const& text) { m_sprite.setTexture(text); }

void Sprite::loadSprite(std::string const& fileName)
{
    m_sprite = sf::Sprite { TextureManager::get(fileName) };
    m_flashSprite = sf::Sprite { TextureManager::get(TextureManager::getFlashName(fileName)) };
}

void Sprite::loadSprite(std::string const& fileName, jt::Recti const& rect)
{
    m_sprite = sf::Sprite { TextureManager::get(fileName), rect };
    m_flashSprite
        = sf::Sprite { TextureManager::get(TextureManager::getFlashName(fileName)), rect };
}

void Sprite::setPosition(jt::Vector2 const& pos) { m_position = pos; }
jt::Vector2 Sprite::getPosition() const { return m_position; }

void Sprite::setColor(jt::Color const& col) { m_sprite.setColor(col); }
jt::Color Sprite::getColor() const { return m_sprite.getColor(); }

void Sprite::setFlashColor(jt::Color const& col) { m_flashSprite.setColor(col); }
jt::Color Sprite::getFlashColor() const { return m_flashSprite.getColor(); }

jt::Rect Sprite::getGlobalBounds() const { return m_sprite.getGlobalBounds(); }
jt::Rect Sprite::getLocalBounds() const { return m_sprite.getLocalBounds(); }

void Sprite::setScale(jt::Vector2 const& scale)
{
    m_sprite.setScale(scale);
    m_flashSprite.setScale(scale);
}

jt::Vector2 Sprite::getScale() const { return m_sprite.getScale(); }

void Sprite::setOrigin(jt::Vector2 const& origin)
{
    m_sprite.setOrigin(origin);
    m_flashSprite.setOrigin(origin);
}

jt::Vector2 Sprite::getOrigin() const { return m_sprite.getOrigin(); }

// WARNING: This function is slow, because it needs to copy
// graphics memory to ram first.
jt::Color Sprite::getColorAtPixel(jt::Vector2u pixelPos) const
{
    if (pixelPos.x() >= static_cast<unsigned int>(m_sprite.getLocalBounds().width)
        || pixelPos.y() >= static_cast<unsigned int>(m_sprite.getLocalBounds().height)) {
        throw std::invalid_argument { "pixel position out of bounds" };
    }
    // optimization to avoid unneccesary copies
    if (!m_imageStored) {
        m_imageStored = true;
        m_image = m_sprite.getTexture()->copyToImage();
    }
    return jt::Color { m_image.getPixel(pixelPos.x(), pixelPos.y()) };
}

void Sprite::cleanImage()
{
    m_imageStored = false;
    m_image = sf::Image {};
}

void Sprite::doUpdate(float /*elapsed*/)
{
    // std::cout << "Sprite.CamOffset.x " << getCamOffset().x() << std::endl;
    auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset();
    // std::cout << "Sprite.final position.x " << pos.x() << std::endl;
    m_sprite.setPosition(pos);
    m_flashSprite.setPosition(pos);
}

void Sprite::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (sptr) {
        jt::Vector2 const oldPos = m_sprite.getPosition();
        jt::Color const oldCol = m_sprite.getColor();

        m_sprite.setPosition(oldPos + getShadowOffset());
        m_sprite.setColor(getShadowColor());
        sptr->draw(m_sprite);

        m_sprite.setPosition(oldPos);
        m_sprite.setColor(oldCol);
    }
}

void Sprite::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (sptr) {
        sptr->draw(m_sprite);
    }
}

void Sprite::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (sptr) {
        sptr->draw(m_flashSprite);
    }
}

void Sprite::doRotate(float rot)
{
    m_sprite.setRotation(-rot);
    m_flashSprite.setRotation(-rot);
}

} // namespace jt
