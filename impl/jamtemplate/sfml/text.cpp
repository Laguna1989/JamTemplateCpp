#include "text.hpp"
#include <color_lib.hpp>
#include <math_helper.hpp>
#include <rect_lib.hpp>
#include <vector_lib.hpp>
#include <iostream>

jt::Text::~Text()
{
    m_text = nullptr;
    m_flashText = nullptr;
    m_font = nullptr;
}

void jt::Text::loadFont(std::string const& fontFileName, unsigned int characterSize,
    std::weak_ptr<jt::RenderTargetLayer> /*wptr*/)
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

void jt::Text::setText(std::string const& text)
{
    m_text->setString(text);
    m_flashText->setString(text);
}

std::string jt::Text::getText() const { return m_text->getString(); }

void jt::Text::setPosition(jt::Vector2f const& pos) { m_position = pos; }

jt::Vector2f jt::Text::getPosition() const { return m_position; }

void jt::Text::setColor(jt::Color const& col) { m_text->setFillColor(toLib(col)); }

jt::Color jt::Text::getColor() const { return fromLib(m_text->getFillColor()); }

jt::Rectf jt::Text::getGlobalBounds() const { return fromLib(m_text->getGlobalBounds()); }

jt::Rectf jt::Text::getLocalBounds() const { return fromLib(m_text->getLocalBounds()); }

void jt::Text::setScale(jt::Vector2f const& scale)
{
    m_text->setScale(toLib(scale));
    m_flashText->setScale(toLib(scale));
}

jt::Vector2f jt::Text::getScale() const { return fromLib(m_text->getScale()); }

void jt::Text::setOriginInternal(jt::Vector2f const& origin)
{
    if (m_text) {
        m_text->setOrigin(toLib(origin));
        m_flashText->setOrigin(toLib(origin));
    }
}

void jt::Text::setTextAlign(jt::Text::TextAlign ta) { m_textAlign = ta; }

jt::Text::TextAlign jt::Text::getTextAlign() const { return m_textAlign; }

void jt::Text::doUpdate(float /*elapsed*/)
{
    m_text->setFont(*m_font);
    m_flashText->setFont(*m_font);

    jt::Vector2f alignOffset { 0, 0 };
    if (m_textAlign == TextAlign::CENTER) {
        alignOffset.x = -m_text->getGlobalBounds().width / 2.0f;
    } else if (m_textAlign == TextAlign::RIGHT) {
        alignOffset.x = -m_text->getGlobalBounds().width;
    }

    auto const position = jt::MathHelper::castToInteger(
        m_position + getShakeOffset() + alignOffset + getCompleteCamOffset());
    // casting to int and back to float avoids blurry text when rendered on non-integer positions

    m_text->setPosition(toLib(position));
    m_flashText->setPosition(toLib(position));
    m_flashText->setScale(m_text->getScale());
}

void jt::Text::doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }

    jt::Vector2f const oldPos = fromLib(m_text->getPosition());
    auto const oldCol = fromLib(m_text->getFillColor());

    auto const position = oldPos + getShadowOffset();

    m_text->setPosition(toLib(jt::MathHelper::castToInteger(position)));
    m_text->setFillColor(toLib(getShadowColor()));
    sptr->draw(*m_text);

    m_text->setPosition(toLib(oldPos));
    m_text->setFillColor(toLib(oldCol));
}

void jt::Text::doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }

    jt::Vector2f const oldPos = fromLib(m_text->getPosition());
    jt::Color const oldCol = fromLib(m_text->getFillColor());

    m_text->setFillColor(toLib(getOutlineColor()));

    for (auto const outlineOffset : getOutlineOffsets()) {
        m_text->setPosition(toLib(jt::MathHelper::castToInteger(oldPos + outlineOffset)));
        sptr->draw(*m_text);
    }

    m_text->setPosition(toLib(oldPos));
    m_text->setFillColor(toLib(oldCol));
}

void jt::Text::doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }

    sf::RenderStates states { getSfBlendMode() };
    sptr->draw(*m_text, states);
}

void jt::Text::doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }

    sptr->draw(*m_flashText);
}

void jt::Text::doRotate(float rot)
{
    m_text->setRotation(rot);
    m_flashText->setRotation(rot);
}
