#ifndef GUARD_JAMTEMPLATE_SMARTTEXT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTTEXT_HPP_INCLUDEGUARD

#include "SmartDrawable.hpp"
#include "rendertarget.hpp"
#include <SFML/Graphics.hpp>
#include <exception>
#include <memory>
#include <string>

namespace jt {

class SmartText : public SmartDrawable {
public:
    enum class TextAlign { CENTER, LEFT, RIGHT };

    using Sptr = std::shared_ptr<SmartText>;

    virtual ~SmartText()
    {
        // std::cout << "SmartText dtor\n";
        m_text = nullptr;
        // std::cout << "SmartText dtor2\n";
        m_flashText = nullptr;
        // std::cout << "SmartText dtor3\n";
        m_font = nullptr;
        // std::cout << "SmartText dtor4\n";
    }

    void loadFont(std::string const& fontFileName, unsigned int characterSize,
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

    void setText(std::string text)
    {
        m_text->setString(text);
        m_flashText->setString(text);
    }
    std::string getText() const { return m_text->getString(); }

    void setOutline(float thickness, jt::color col)
    {
        m_text->setOutlineThickness(thickness);
        m_text->setOutlineColor(col);
    }

    void setPosition(jt::vector2 const& pos) override { m_position = pos; }

    const jt::vector2 getPosition() const override { return m_position; }

    void setColor(const jt::color& col) override { m_text->setFillColor(col); }
    const jt::color getColor() const override { return m_text->getFillColor(); }

    void setFlashColor(const jt::color& col) override { m_flashText->setFillColor(col); }
    const jt::color getFlashColor() const override { return m_flashText->getFillColor(); }

    // virtual sf::Transform const getTransform() const override { return m_text->getTransform(); }

    jt::rect const getGlobalBounds() const override { return m_text->getGlobalBounds(); }
    jt::rect const getLocalBounds() const override { return m_text->getLocalBounds(); }

    virtual void setScale(jt::vector2 const& scale)
    {
        m_text->setScale(scale);
        m_flashText->setScale(scale);
    }

    virtual const jt::vector2 getScale() const { return m_text->getScale(); }

    virtual void setOrigin(jt::vector2 const& origin)
    {
        m_text->setOrigin(origin);
        m_flashText->setOrigin(origin);
    }

    virtual const jt::vector2 getOrigin() const { return m_text->getOrigin(); }

    void SetTextAlign(TextAlign ta) { m_textAlign = ta; }
    TextAlign getTextAlign() const { return m_textAlign; }

private:
    mutable std::shared_ptr<sf::Text> m_text;
    std::shared_ptr<sf::Text> m_flashText;
    std::shared_ptr<sf::Font> m_font;

    TextAlign m_textAlign { TextAlign::CENTER };

    jt::vector2 m_position { 0, 0 };

    void doUpdate(float /*elapsed*/) override
    {
        m_text->setFont(*m_font);
        m_flashText->setFont(*m_font);

        jt::vector2 alignOffset { 0, 0 };
        if (m_textAlign == TextAlign::CENTER) {
            alignOffset.x() = -m_text->getGlobalBounds().width / 2.0f;
        }

        jt::vector2 pos = m_position + getShakeOffset() + alignOffset + getCamOffset();

        m_text->setPosition(jt::vector2 { pos.x(), pos.y() });
        m_flashText->setPosition(m_text->getPosition());
        m_flashText->setScale(m_text->getScale());
    }

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        jt::vector2 const oldPos = m_text->getPosition();
        jt::color const oldCol = m_text->getFillColor();

        m_text->setPosition(oldPos + getShadowOffset());
        m_text->setFillColor(getShadowColor());
        sptr->draw(*m_text);

        m_text->setPosition(oldPos);
        m_text->setFillColor(oldCol);
    }

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        try {
            sptr->draw(*m_text);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        } catch (...) {
            std::cerr << "error drawing text" << std::endl;
        }
    }

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        sptr->draw(*m_flashText);
    }

    void doRotate(float rot) override
    {
        m_text->setRotation(-rot);
        m_flashText->setRotation(-rot);
    }
};
} // namespace jt

#endif
