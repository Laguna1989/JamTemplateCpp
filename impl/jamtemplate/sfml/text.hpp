#ifndef GUARD_JAMTEMPLATE_TEXT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TEXT_HPP_INCLUDEGUARD

#include "drawable_impl.hpp"
#include "render_target.hpp"
#include <SFML/Graphics.hpp>

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
        std::weak_ptr<jt::RenderTarget> rendertarget_wptr /*unused*/);

    void setText(std::string text);
    std::string getText() const;

    void setOutline(float thickness, jt::Color col);
    void setPosition(jt::Vector2f const& pos) override;

    jt::Vector2f getPosition() const override;

    void setColor(const jt::Color& col) override;
    jt::Color getColor() const override;

    void setFlashColor(const jt::Color& col) override;
    jt::Color getFlashColor() const override;

    jt::Rectf getGlobalBounds() const override;
    jt::Rectf getLocalBounds() const override;

    void setScale(jt::Vector2f const& scale) override;

    jt::Vector2f getScale() const override;

    virtual void setOrigin(jt::Vector2f const& origin);

    virtual jt::Vector2f getOrigin() const;

    void setTextAlign(TextAlign ta);
    TextAlign getTextAlign() const;

private:
    mutable std::shared_ptr<sf::Text> m_text;
    std::shared_ptr<sf::Text> m_flashText;
    std::shared_ptr<sf::Font> m_font;

    TextAlign m_textAlign { TextAlign::CENTER };

    jt::Vector2f m_position { 0, 0 };

    void doUpdate(float /*elapsed*/) override;

    void doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const override;
    void doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::RenderTarget> const sptr) const override;

    void doRotate(float rot) override;
};
} // namespace jt

#endif
