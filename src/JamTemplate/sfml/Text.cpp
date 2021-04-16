#include "Text.hpp"

namespace jt {

Text::~Text()
{
    // std::cout << "Text dtor\n";
    m_text = nullptr;
    // std::cout << "Text dtor2\n";
    m_flashText = nullptr;
    // std::cout << "Text dtor3\n";
    m_font = nullptr;
    // std::cout << "Text dtor4\n";
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
const jt::Vector2 Text::getPosition() const { return m_position; }

void Text::setColor(const jt::Color& col) { m_text->setFillColor(col); }
const jt::Color Text::getColor() const { return m_text->getFillColor(); }

void Text::setFlashColor(const jt::Color& col) { m_flashText->setFillColor(col); }
const jt::Color Text::getFlashColor() const { return m_flashText->getFillColor(); }

//  sf::Transform const getTransform() const  { return m_text->getTransform(); }

jt::Rect const Text::getGlobalBounds() const { return m_text->getGlobalBounds(); }
jt::Rect const Text::getLocalBounds() const { return m_text->getLocalBounds(); }

void Text::setScale(jt::Vector2 const& scale)
{
    m_text->setScale(scale);
    m_flashText->setScale(scale);
}

const jt::Vector2 Text::getScale() const { return m_text->getScale(); }

void Text::setOrigin(jt::Vector2 const& origin)
{
    m_text->setOrigin(origin);
    m_flashText->setOrigin(origin);
}

const jt::Vector2 Text::getOrigin() const { return m_text->getOrigin(); }

void Text::SetTextAlign(Text::TextAlign ta) { m_textAlign = ta; }
Text::TextAlign Text::getTextAlign() const { return m_textAlign; }

void Text::doUpdate(float /*elapsed*/)
{
    m_text->setFont(*m_font);
    m_flashText->setFont(*m_font);

    jt::Vector2 alignOffset { 0, 0 };
    if (m_textAlign == TextAlign::CENTER) {
        alignOffset.x() = -m_text->getGlobalBounds().width / 2.0f;
    }

    jt::Vector2 pos = m_position + getShakeOffset() + alignOffset + getCamOffset();

    m_text->setPosition(jt::Vector2 { pos.x(), pos.y() });
    m_flashText->setPosition(m_text->getPosition());
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

void Text::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    try {
        sptr->draw(*m_text);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cerr << "error drawing text" << std::endl;
    }
}

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
