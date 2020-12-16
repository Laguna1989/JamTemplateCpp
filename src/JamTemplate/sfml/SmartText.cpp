#include "SmartText.hpp"

namespace jt {

SmartText::~SmartText()
{
    // std::cout << "SmartText dtor\n";
    m_text = nullptr;
    // std::cout << "SmartText dtor2\n";
    m_flashText = nullptr;
    // std::cout << "SmartText dtor3\n";
    m_font = nullptr;
    // std::cout << "SmartText dtor4\n";
}

void SmartText::loadFont(std::string const& fontFileName, unsigned int characterSize,
    std::weak_ptr<jt::renderTarget> wptr /*unused*/)
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

void SmartText::setText(std::string text)
{
    m_text->setString(text);
    m_flashText->setString(text);
}
std::string SmartText::getText() const { return m_text->getString(); }

void SmartText::setOutline(float thickness, jt::Color col)
{
    m_text->setOutlineThickness(thickness);
    m_text->setOutlineColor(col);
}

void SmartText::setPosition(jt::Vector2 const& pos) { m_position = pos; }
const jt::Vector2 SmartText::getPosition() const { return m_position; }

void SmartText::setColor(const jt::Color& col) { m_text->setFillColor(col); }
const jt::Color SmartText::getColor() const { return m_text->getFillColor(); }

void SmartText::setFlashColor(const jt::Color& col) { m_flashText->setFillColor(col); }
const jt::Color SmartText::getFlashColor() const { return m_flashText->getFillColor(); }

//  sf::Transform const getTransform() const  { return m_text->getTransform(); }

jt::Rect const SmartText::getGlobalBounds() const { return m_text->getGlobalBounds(); }
jt::Rect const SmartText::getLocalBounds() const { return m_text->getLocalBounds(); }

void SmartText::setScale(jt::Vector2 const& scale)
{
    m_text->setScale(scale);
    m_flashText->setScale(scale);
}

const jt::Vector2 SmartText::getScale() const { return m_text->getScale(); }

void SmartText::setOrigin(jt::Vector2 const& origin)
{
    m_text->setOrigin(origin);
    m_flashText->setOrigin(origin);
}

const jt::Vector2 SmartText::getOrigin() const { return m_text->getOrigin(); }

void SmartText::SetTextAlign(SmartText::TextAlign ta) { m_textAlign = ta; }
SmartText::TextAlign SmartText::getTextAlign() const { return m_textAlign; }

void SmartText::doUpdate(float /*elapsed*/)
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

void SmartText::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    jt::Vector2 const oldPos = m_text->getPosition();
    jt::Color const oldCol = m_text->getFillColor();

    m_text->setPosition(oldPos + getShadowOffset());
    m_text->setFillColor(getShadowColor());
    sptr->draw(*m_text);

    m_text->setPosition(oldPos);
    m_text->setFillColor(oldCol);
}

void SmartText::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    try {
        sptr->draw(*m_text);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cerr << "error drawing text" << std::endl;
    }
}

void SmartText::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    sptr->draw(*m_flashText);
}

void SmartText::doRotate(float rot)
{
    m_text->setRotation(-rot);
    m_flashText->setRotation(-rot);
}

} // namespace jt
