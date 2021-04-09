#ifndef GUARD_JAMTEMPLATE_TEXT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TEXT_HPP_INCLUDEGUARD

#include "DrawableImpl.hpp"
#include "Rendertarget.hpp"
#include <SFML/Graphics.hpp>
#include <exception>
#include <memory>
#include <string>

namespace jt {

class Text : public DrawableImpl {
public:
    enum class TextAlign { CENTER, LEFT, RIGHT };

    using Sptr = std::shared_ptr<Text>;

    virtual ~Text();

    // note: it is ok to pass a nullptr as rendertarget_wptr for sfml.
    void loadFont(std::string const& fontFileName, unsigned int characterSize,
        std::weak_ptr<jt::renderTarget> rendertarget_wptr /*unused*/);

    void setText(std::string text);
    std::string getText() const;

    void setOutline(float thickness, jt::Color col);
    void setPosition(jt::Vector2 const& pos) override;

    const jt::Vector2 getPosition() const override;

    void setColor(const jt::Color& col) override;
    const jt::Color getColor() const override;

    void setFlashColor(const jt::Color& col) override;
    const jt::Color getFlashColor() const override;

    // virtual sf::Transform const getTransform() const override { return m_text->getTransform(); }

    jt::Rect const getGlobalBounds() const override;
    jt::Rect const getLocalBounds() const override;

    virtual void setScale(jt::Vector2 const& scale);

    virtual const jt::Vector2 getScale() const;

    virtual void setOrigin(jt::Vector2 const& origin);

    virtual const jt::Vector2 getOrigin() const;

    void SetTextAlign(TextAlign ta);
    TextAlign getTextAlign() const;

private:
    mutable std::shared_ptr<sf::Text> m_text;
    std::shared_ptr<sf::Text> m_flashText;
    std::shared_ptr<sf::Font> m_font;

    TextAlign m_textAlign { TextAlign::CENTER };

    jt::Vector2 m_position { 0, 0 };

    void doUpdate(float /*elapsed*/) override;

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doRotate(float rot) override;
};
} // namespace jt

#endif
