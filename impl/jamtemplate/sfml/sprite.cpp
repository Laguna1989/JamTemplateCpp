#include "sprite.hpp"
#include "color_lib.hpp"
#include "rect_lib.hpp"
#include "vector_lib.hpp"

namespace jt {

Sprite::Sprite() { }

Sprite::Sprite(std::string const& fileName, jt::TextureManagerInterface& textureManager)
{
    m_sprite = sf::Sprite { textureManager.get(fileName) };
    m_flashSprite = sf::Sprite { textureManager.get(textureManager.getFlashName(fileName)) };
}

Sprite::Sprite(
    std::string const& fileName, jt::Recti const& rect, jt::TextureManagerInterface& textureManager)
{
    m_sprite = sf::Sprite { textureManager.get(fileName), toLib(rect) };
    m_flashSprite
        = sf::Sprite { textureManager.get(textureManager.getFlashName(fileName)), toLib(rect) };
}

void Sprite::fromTexture(sf::Texture const& text) { m_sprite.setTexture(text); }

void Sprite::setPosition(jt::Vector2f const& pos) { m_position = pos; }
jt::Vector2f Sprite::getPosition() const { return m_position; }

void Sprite::setColor(jt::Color const& col) { m_sprite.setColor(toLib(col)); }
jt::Color Sprite::getColor() const { return fromLib(m_sprite.getColor()); }

void Sprite::setFlashColor(jt::Color const& col) { m_flashSprite.setColor(toLib(col)); }
jt::Color Sprite::getFlashColor() const { return fromLib(m_flashSprite.getColor()); }

jt::Rectf Sprite::getGlobalBounds() const { return fromLib(m_sprite.getGlobalBounds()); }
jt::Rectf Sprite::getLocalBounds() const { return fromLib(m_sprite.getLocalBounds()); }

void Sprite::setScale(jt::Vector2f const& scale)
{
    m_sprite.setScale(toLib(scale));
    m_flashSprite.setScale(toLib(scale));
}

jt::Vector2f Sprite::getScale() const { return fromLib(m_sprite.getScale()); }

void Sprite::setOrigin(jt::Vector2f const& origin)
{
    m_sprite.setOrigin(toLib(origin));
    m_flashSprite.setOrigin(toLib(origin));
}

jt::Vector2f Sprite::getOrigin() const { return fromLib(m_sprite.getOrigin()); }

// WARNING: This function is slow, because it needs to copy
// graphics memory to ram first.
jt::Color Sprite::getColorAtPixel(jt::Vector2u pixelPos) const
{
    if (pixelPos.x >= static_cast<unsigned int>(m_sprite.getLocalBounds().width)
        || pixelPos.y >= static_cast<unsigned int>(m_sprite.getLocalBounds().height)) {
        throw std::invalid_argument { "pixel position out of bounds" };
    }
    // optimization to avoid unnecessary copies
    if (!m_imageStored) {
        m_imageStored = true;
        m_image = m_sprite.getTexture()->copyToImage();
    }
    return jt::Color { fromLib(m_image.getPixel(pixelPos.x, pixelPos.y)) };
}

void Sprite::cleanImage()
{
    m_imageStored = false;
    m_image = sf::Image {};
}

void Sprite::doUpdate(float /*elapsed*/)
{
    // std::cout << "Sprite.CamOffset.x " << getCamOffset().x << std::endl;
    auto const pos = m_position + getShakeOffset() + getOffset() + getCamOffset();
    // std::cout << "Sprite.final position.x " << pos.x << std::endl;
    m_sprite.setPosition(toLib(pos));
    m_flashSprite.setPosition(toLib(pos));
}

void Sprite::doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    if (sptr) {
        jt::Vector2f const oldPos = fromLib(m_sprite.getPosition());
        auto const oldCol = fromLib(m_sprite.getColor());

        m_sprite.setPosition(toLib(oldPos + getShadowOffset()));
        m_sprite.setColor(toLib(getShadowColor()));
        sptr->draw(m_sprite);

        m_sprite.setPosition(toLib(oldPos));
        m_sprite.setColor(toLib(oldCol));
    }
}

void Sprite::doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    if (sptr) {
        sptr->draw(m_sprite);
    }
}

void Sprite::doDrawFlash(std::shared_ptr<jt::RenderTarget> const sptr) const
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
