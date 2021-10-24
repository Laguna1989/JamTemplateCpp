#include "text.hpp"
#include <iostream>

namespace jt {

Text::~Text()
{
    m_text = nullptr;
    m_flashText = nullptr;
    m_font = nullptr;
}

void Text::loadFont(std::string const& fontFileName, unsigned int characterSize,
    std::weak_ptr<jt::renderTarget> /*wptr*/)
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
    m_text->setOutlineColor(col);
}

void Text::setPosition(jt::Vector2 const& pos) { m_position = pos; }
jt::Vector2 Text::getPosition() const { return m_position; }

void Text::setColor(const jt::Color& col) { m_text->setFillColor(col); }
jt::Color Text::getColor() const { return m_text->getFillColor(); }

void Text::setFlashColor(const jt::Color& col) { m_flashText->setFillColor(col); }
jt::Color Text::getFlashColor() const { return m_flashText->getFillColor(); }

//  sf::Transform const getTransform() const  { return m_text->getTransform(); }

jt::Rect Text::getGlobalBounds() const { return m_text->getGlobalBounds(); }
jt::Rect Text::getLocalBounds() const { return m_text->getLocalBounds(); }

void Text::setScale(jt::Vector2 const& scale)
{
    m_text->setScale(scale);
    m_flashText->setScale(scale);
}

jt::Vector2 Text::getScale() const { return m_text->getScale(); }

void Text::setOrigin(jt::Vector2 const& origin)
{
    m_text->setOrigin(origin);
    m_flashText->setOrigin(origin);
}

jt::Vector2 Text::getOrigin() const { return m_text->getOrigin(); }

void Text::setTextAlign(Text::TextAlign ta) { m_textAlign = ta; }
Text::TextAlign Text::getTextAlign() const { return m_textAlign; }

void Text::doUpdate(float /*elapsed*/)
{
    m_text->setFont(*m_font);
    m_flashText->setFont(*m_font);

    jt::Vector2 alignOffset { 0, 0 };
    if (m_textAlign == TextAlign::CENTER) {
        alignOffset.x() = -m_text->getGlobalBounds().width / 2.0f;
    } else if (m_textAlign == TextAlign::RIGHT) {
        alignOffset.x() = -m_text->getGlobalBounds().width;
    }

    jt::Vector2 const position = m_position + getShakeOffset() + alignOffset + getCamOffset();
    // casting to int and back to float avoids blurry text when rendered on non-integer positions
    jt::Vector2 const pos = jt::Vector2 { static_cast<float>(static_cast<int>(position.x())),
        static_cast<float>(static_cast<int>(position.y())) };

    m_text->setPosition(pos);
    m_flashText->setPosition(pos);
    m_flashText->setScale(m_text->getScale());
}

void Text::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    jt::Vector2 const oldPos = m_text->getPosition();
    jt::Color const oldCol = m_text->getFillColor();

    m_text->setPosition(oldPos + getShadowOffset());
    m_text->setFillColor(getShadowColor());
    sptr->draw(*m_text);

    m_text->setPosition(oldPos);
    m_text->setFillColor(oldCol);
}

void Text::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const { sptr->draw(*m_text); }

void Text::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    sptr->draw(*m_flashText);
}

void Text::doRotate(float rot)
{
    m_text->setRotation(-rot);
    m_flashText->setRotation(-rot);
}

} // namespace jt
