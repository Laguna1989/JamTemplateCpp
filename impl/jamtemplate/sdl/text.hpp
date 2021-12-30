#ifndef GUARD_JAMTEMPLATE_TEXT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TEXT_HPP_INCLUDEGUARD

#include "drawable_impl.hpp"
#include "render_target.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <string>
#include <vector>

namespace jt {

class Text : public DrawableImpl {
public:
    enum class TextAlign { CENTER, LEFT, RIGHT };

    using Sptr = std::shared_ptr<Text>;

    virtual ~Text();

    void loadFont(std::string const& fontFileName, unsigned int characterSize,
        std::weak_ptr<jt::RenderTarget> wptr);

    void setText(std::string const& text);
    std::string getText() const;

    void setOutline(float /*thickness*/, jt::Color /*col*/);

    void setPosition(jt::Vector2f const& pos) override;

    jt::Vector2f getPosition() const override;

    void setColor(const jt::Color& col) override;
    jt::Color getColor() const override;

    void setFlashColor(const jt::Color& col) override;
    jt::Color getFlashColor() const override;

    jt::Rectf getGlobalBounds() const override;
    jt::Rectf getLocalBounds() const override;

    virtual void setScale(jt::Vector2f const& scale) override;

    virtual jt::Vector2f getScale() const override;

    virtual void setOrigin(jt::Vector2f const& origin) override;

    virtual jt::Vector2f getOrigin() const override;

    void setTextAlign(TextAlign ta);
    TextAlign getTextAlign() const;

private:
    TTF_Font* m_font { nullptr };
    std::string m_text { "" };

    TextAlign m_textAlign { TextAlign::CENTER };

    jt::Vector2f m_position { 0, 0 };
    jt::Color m_color { jt::colors::White };
    jt::Color m_flashColor { jt::colors::White };
    jt::Vector2f m_origin { 0.0f, 0.0f };
    jt::Vector2f m_scale { 1.0f, 1.0f };
    jt::Vector2f m_offsetFromOrigin { 0.0f, 0.0f };

    // optimization, so the text rendering logic does not have to happen in every frame, but only
    // when the text changes.
    mutable std::shared_ptr<SDL_Texture> m_textTexture { nullptr };
    int m_textTextureSizeX { 0 };
    int m_textTextureSizeY { 0 };

    std::weak_ptr<jt::RenderTarget> m_rendertarget;

    void doUpdate(float /*elapsed*/) override;

    void doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const override;

    void renderOneLineOfText(std::shared_ptr<jt::RenderTarget> const sptr, std::string text,
        std::size_t i, std::size_t lineCount) const;

    jt::Vector2u getSizeForLine(
        std::shared_ptr<jt::RenderTarget> const sptr, std::string const& text) const;

    void doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const override;

    void doDrawFlash(std::shared_ptr<jt::RenderTarget> const /*sptr*/) const override;

    void doRotate(float /*rot*/) override;

    void recreateTextTexture(std::shared_ptr<jt::RenderTarget> const sptr);
    std::shared_ptr<jt::RenderTarget> getRenderTarget();
    void setSDLColor(jt::Color const& col) const;
    SDL_Rect getDestRect(jt::Vector2f const& positionOffset = jt::Vector2f { 0.0f, 0.0f }) const;

    int getUpscaleFactor() const { return 1; };
    void calculateTextTextureSize(
        std::shared_ptr<jt::RenderTarget> const sptr, std::vector<std::string> const& ssv);
};
} // namespace jt

#endif
