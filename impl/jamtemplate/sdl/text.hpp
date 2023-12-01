#ifndef JAMTEMPLATE_TEXT_HPP
#define JAMTEMPLATE_TEXT_HPP

#include <drawable_impl_sdl.hpp>
#include <render_target_layer.hpp>
#include <sdl_2_include.hpp>
#include <memory>
#include <string>
#include <vector>

namespace jt {

class Text : public DrawableImplSdl {
public:
    enum class TextAlign { CENTER, LEFT, RIGHT };

    using Sptr = std::shared_ptr<Text>;

    ~Text() override;

    /// load Font
    /// \param fontFileName filename to the font (ttf)
    /// \param characterSize size in characters
    /// \param rendertarget_wptr the rendertarget (unused for sfml, but needed for sdl
    /// compatibility)
    void loadFont(std::string const& fontFileName, unsigned int characterSize,
        std::weak_ptr<jt::RenderTargetLayer> wptr);

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

    void setPosition(jt::Vector2f const& pos) noexcept override;
    jt::Vector2f getPosition() const noexcept override;

    void setColor(jt::Color const& col) noexcept override;
    jt::Color getColor() const noexcept override;

    jt::Rectf getGlobalBounds() const override;
    jt::Rectf getLocalBounds() const override;

    void setScale(jt::Vector2f const& scale) override;

    jt::Vector2f getScale() const noexcept override;

private:
    TTF_Font* m_font { nullptr };
    std::string m_text { "" };

    TextAlign m_textAlign { TextAlign::CENTER };

    jt::Vector2f m_position { 0, 0 };
    jt::Color m_color { jt::colors::White };

    // optimization, so the text rendering logic does not have to happen in every frame, but only
    // when the text changes.
    mutable std::shared_ptr<SDL_Texture> m_textTexture { nullptr };
    int m_textTextureSizeX { 0 };
    int m_textTextureSizeY { 0 };

    std::weak_ptr<jt::RenderTargetLayer> m_rendertarget;

    void doUpdate(float /*elapsed*/) override;

    void renderOneLineOfText(std::shared_ptr<jt::RenderTargetLayer> const sptr, std::string text,
        std::size_t i, std::size_t lineCount) const;

    jt::Vector2u getSizeForLine(
        std::shared_ptr<jt::RenderTargetLayer> const sptr, std::string const& text) const;

    void doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;

    void doRotate(float /*rot*/) noexcept override;

    void recreateTextTexture(std::shared_ptr<jt::RenderTargetLayer> const sptr);
    std::shared_ptr<jt::RenderTargetLayer> getRenderTarget();
    void setSDLColor(jt::Color const& col) const;
    SDL_Rect getDestRect(jt::Vector2f const& positionOffset = jt::Vector2f { 0.0f, 0.0f }) const;

    void calculateTextTextureSize(
        std::shared_ptr<jt::RenderTargetLayer> const sptr, std::vector<std::string> const& ssv);
};
} // namespace jt

#endif
