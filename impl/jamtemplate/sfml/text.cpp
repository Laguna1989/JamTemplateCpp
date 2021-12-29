#include "text.hpp"
#include "color_lib.hpp"
#include "rect_lib.hpp"
#include "vector_lib.hpp"
#include <iostream>

namespace jt {

Text::~Text()
{
    m_text = nullptr;
    m_flashText = nullptr;
    m_font = nullptr;
}

void Text::loadFont(std::string const& fontFileName, unsigned int characterSize,
    std::weak_ptr<jt::RenderTarget> /*wptr*/)
{
    m_font = std::make_shared<sf::Font>();
    if (!m_font->loadFromFile(fontFileName)) {
        std::cerr << "cannot load font: " << fontFileName << std::endl;
    }
    m_text = std::make_shared<sf::Text>("", *m_font, 8);
    m_flashText = std::make_shared<sf::Text>("", *m_font, 8);
    m_text->setCharacterSize(characterSize);
    m_flashText->setCharacterSize(characterSize);
}

void Text::setText(std::string text)
{
    m_text->setString(text);
    m_flashText->setString(text);
}
std::string Text::getText() const { return m_text->getString(); }

void Text::setOutline(float thickness, jt::Color col)
{
    m_text->setOutlineThickness(thickness);
    m_text->setOutlineColor(toLib(col));
}

void Text::setPosition(jt::Vector2f const& pos) { m_position = pos; }
jt::Vector2f Text::getPosition() const { return m_position; }

void Text::setColor(const jt::Color& col) { m_text->setFillColor(toLib(col)); }
jt::Color Text::getColor() const { return fromLib(m_text->getFillColor()); }

void Text::setFlashColor(const jt::Color& col) { m_flashText->setFillColor(toLib(col)); }
jt::Color Text::getFlashColor() const { return fromLib(m_flashText->getFillColor()); }

jt::Rectf Text::getGlobalBounds() const { return fromLib(m_text->getGlobalBounds()); }
jt::Rectf Text::getLocalBounds() const { return fromLib(m_text->getLocalBounds()); }

void Text::setScale(jt::Vector2f const& scale)
{
    m_text->setScale(toLib(scale));
    m_flashText->setScale(toLib(scale));
}

jt::Vector2f Text::getScale() const { return fromLib(m_text->getScale()); }

void Text::setOrigin(jt::Vector2f const& origin)
{
    m_text->setOrigin(toLib(origin));
    m_flashText->setOrigin(toLib(origin));
}

jt::Vector2f Text::getOrigin() const { return fromLib(m_text->getOrigin()); }

void Text::setTextAlign(Text::TextAlign ta) { m_textAlign = ta; }
Text::TextAlign Text::getTextAlign() const { return m_textAlign; }

void Text::doUpdate(float /*elapsed*/)
{
    m_text->setFont(*m_font);
    m_flashText->setFont(*m_font);

    jt::Vector2f alignOffset { 0, 0 };
    if (m_textAlign == TextAlign::CENTER) {
        alignOffset.x = -m_text->getGlobalBounds().width / 2.0f;
    } else if (m_textAlign == TextAlign::RIGHT) {
        alignOffset.x = -m_text->getGlobalBounds().width;
    }

    jt::Vector2f const position = m_position + getShakeOffset() + alignOffset + getCamOffset();
    // casting to int and back to float avoids blurry text when rendered on non-integer positions
    jt::Vector2f const pos = jt::Vector2f { static_cast<float>(static_cast<int>(position.x)),
        static_cast<float>(static_cast<int>(position.y)) };

    m_text->setPosition(toLib(pos));
    m_flashText->setPosition(toLib(pos));
    m_flashText->setScale(m_text->getScale());
}

void Text::doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    jt::Vector2f const oldPos = fromLib(m_text->getPosition());
    auto const oldCol = fromLib(m_text->getFillColor());

    m_text->setPosition(toLib(oldPos + getShadowOffset()));
    m_text->setFillColor(toLib(getShadowColor()));
    sptr->draw(*m_text);

    m_text->setPosition(toLib(oldPos));
    m_text->setFillColor(toLib(oldCol));
}

void Text::doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const { sptr->draw(*m_text); }

void Text::doDrawFlash(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    sptr->draw(*m_flashText);
}

void Text::doRotate(float rot)
{
    m_text->setRotation(-rot);
    m_flashText->setRotation(-rot);
}

} // namespace jt
