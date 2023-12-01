#ifndef JAMTEMPLATE_TEXT_HPP
#define JAMTEMPLATE_TEXT_HPP

#include <SFML/Graphics.hpp>
#include <drawable_impl_sfml.hpp>
#include <render_target_layer.hpp>
#include <memory>
#include <string>

namespace jt {

class Text : public DrawableImplSFML {
public:
    enum class TextAlign { CENTER, LEFT, RIGHT };

    using Sptr = std::shared_ptr<Text>;

    ~Text() override;

    // note: it is ok to pass a nullptr as rendertarget_wptr for sfml.
    /// load Font
    /// \param fontFileName filename to the font (ttf)
    /// \param characterSize size in characters
    /// \param rendertarget_wptr the rendertarget (unused for sfml, but needed for sdl compatibility)
    void loadFont(std::string const& fontFileName, unsigned int characterSize,
        std::weak_ptr<jt::RenderTargetLayer> rendertarget_wptr /*unused*/);

    /// set the text
    /// \param text the text to be displayed
    void setText(std::string const& text);

    /// get the text
    /// \return the text
    std::string getText() const;

    /// set the text alignment
    /// \param ta the text alignment
    void setTextAlign(TextAlign ta);

    /// get the text alignment
    /// \return the text alignment
    TextAlign getTextAlign() const;

    // override from DrawableImpl

    void setPosition(jt::Vector2f const& pos) override;
    jt::Vector2f getPosition() const override;

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    jt::Rectf getGlobalBounds() const override;
    jt::Rectf getLocalBounds() const override;

    void setScale(jt::Vector2f const& scale) override;
    jt::Vector2f getScale() const override;

    void setOriginInternal(jt::Vector2f const& origin) override;
private:
    mutable std::shared_ptr<sf::Text> m_text;
    std::shared_ptr<sf::Text> m_flashText;
    std::shared_ptr<sf::Font> m_font;

    TextAlign m_textAlign { TextAlign::CENTER };

    jt::Vector2f m_position { 0, 0 };

    void doUpdate(float /*elapsed*/) override;

    void doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doRotate(float rot) override;
};
} // namespace jt

#endif
