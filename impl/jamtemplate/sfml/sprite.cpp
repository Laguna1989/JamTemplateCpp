#include "sprite.hpp"
#include <color_lib.hpp>
#include <math_helper.hpp>
#include <rect_lib.hpp>
#include <vector_lib.hpp>

jt::Sprite::Sprite() { }

jt::Sprite::Sprite(std::string const& fileName, jt::TextureManagerInterface& textureManager)
    : m_sprite { sf::Sprite { textureManager.get(fileName) } }
    , m_flashSprite { sf::Sprite { textureManager.get(textureManager.getFlashName(fileName)) } }
{
}

jt::Sprite::Sprite(
    std::string const& fileName, jt::Recti const& rect, jt::TextureManagerInterface& textureManager)
    : m_sprite { sf::Sprite { textureManager.get(fileName), toLib(rect) } }
    , m_flashSprite { sf::Sprite {
          textureManager.get(textureManager.getFlashName(fileName)), toLib(rect) } }
{
}

void jt::Sprite::fromTexture(sf::Texture const& text) { m_sprite.setTexture(text); }

void jt::Sprite::setPosition(jt::Vector2f const& pos) { m_position = pos; }

jt::Vector2f jt::Sprite::getPosition() const { return m_position; }

void jt::Sprite::setColor(jt::Color const& col) { m_sprite.setColor(toLib(col)); }

jt::Color jt::Sprite::getColor() const { return fromLib(m_sprite.getColor()); }

jt::Rectf jt::Sprite::getGlobalBounds() const { return fromLib(m_sprite.getGlobalBounds()); }

jt::Rectf jt::Sprite::getLocalBounds() const { return fromLib(m_sprite.getLocalBounds()); }

void jt::Sprite::setScale(jt::Vector2f const& scale)
{
    m_sprite.setScale(scale.x, scale.y);
    m_flashSprite.setScale(scale.x, scale.y);
}

jt::Vector2f jt::Sprite::getScale() const { return fromLib(m_sprite.getScale()); }

// WARNING: This function is slow, because it needs to copy
// graphics memory to ram first.
jt::Color jt::Sprite::getColorAtPixel(jt::Vector2u pixelPos) const
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

void jt::Sprite::cleanImage() noexcept
{
    m_imageStored = false;
    m_image = sf::Image {};
}

void jt::Sprite::doUpdate(float /*elapsed*/)
{
    m_lastScreenPosition = toLib(jt::MathHelper::castToInteger(
        getPosition() + getShakeOffset() + getOffset() + getCompleteCamOffset()));
    m_sprite.setPosition(m_lastScreenPosition);
}

void jt::Sprite::doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }
    jt::Vector2f const oldPos = fromLib(m_sprite.getPosition());
    auto const oldCol = fromLib(m_sprite.getColor());

    m_sprite.setPosition(toLib(jt::MathHelper::castToInteger(oldPos + getShadowOffset())));
    m_sprite.setColor(toLib(getShadowColor()));
    sptr->draw(m_sprite);

    m_sprite.setPosition(toLib(oldPos));
    m_sprite.setColor(toLib(oldCol));
}

void jt::Sprite::doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }

    jt::Vector2f const oldPos = fromLib(m_sprite.getPosition());
    jt::Color const oldCol = fromLib(m_sprite.getColor());

    auto col = getOutlineColor();
    col.a = oldCol.a;
    m_sprite.setColor(toLib(col));

    for (auto const outlineOffset : getOutlineOffsets()) {
        m_sprite.setPosition(toLib(jt::MathHelper::castToInteger(oldPos + outlineOffset)));
        sptr->draw(m_sprite);
    }

    m_sprite.setPosition(toLib(oldPos));
    m_sprite.setColor(toLib(oldCol));
}

void jt::Sprite::doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }

    sf::RenderStates const states { getSfBlendMode() };
    sptr->draw(m_sprite, states);
}

void jt::Sprite::doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }

    m_flashSprite.setPosition(m_lastScreenPosition);
    m_flashSprite.setColor(toLib(getFlashColor()));
    sptr->draw(m_flashSprite);
}

void jt::Sprite::doRotate(float rot)
{
    m_sprite.setRotation(rot);
    m_flashSprite.setRotation(rot);
}

void jt::Sprite::setOriginInternal(jt::Vector2f const& origin)
{
    m_sprite.setOrigin(origin.x, origin.y);
    m_flashSprite.setOrigin(origin.x, origin.y);
}
