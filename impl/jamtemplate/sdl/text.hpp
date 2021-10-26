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
        std::weak_ptr<jt::renderTarget> wptr);

    void setText(std::string const& text);
    std::string getText() const;

    void setOutline(float /*thickness*/, jt::Color /*col*/);

    void setPosition(jt::Vector2 const& pos) override;

    jt::Vector2 getPosition() const override;

    void setColor(const jt::Color& col) override;
    jt::Color getColor() const override;

    void setFlashColor(const jt::Color& col) override;
    jt::Color getFlashColor() const override;

    // virtual sf::Transform const getTransform() const override { return m_text->getTransform(); }

    jt::Rect getGlobalBounds() const override;
    jt::Rect getLocalBounds() const override;

    virtual void setScale(jt::Vector2 const& scale) override;

    virtual jt::Vector2 getScale() const override;

    virtual void setOrigin(jt::Vector2 const& origin) override;

    virtual jt::Vector2 getOrigin() const override;

    void setTextAlign(TextAlign ta);
    TextAlign getTextAlign() const;

private:
    TTF_Font* m_font { nullptr };
    std::string m_text { "" };

    TextAlign m_textAlign { TextAlign::CENTER };

    jt::Vector2 m_position { 0, 0 };
    jt::Color m_color { jt::colors::White };
    jt::Color m_flashColor { jt::colors::White };
    jt::Vector2 m_origin { 0.0f, 0.0f };
    jt::Vector2 m_scale { 1.0f, 1.0f };
    jt::Vector2 m_offsetFromOrigin { 0.0f, 0.0f };

    // optimization, so the text rendering logic does not have to happen in every frame, but only
    // when the text changes.
    mutable std::shared_ptr<SDL_Texture> m_textTexture { nullptr };
    int m_textTextureSizeX { 0 };
    int m_textTextureSizeY { 0 };

    std::weak_ptr<jt::renderTarget> m_rendertarget;

    void doUpdate(float /*elapsed*/) override;

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void renderOneLineOfText(std::shared_ptr<jt::renderTarget> const sptr, std::string text,
        std::size_t i, std::size_t lineCount) const;

    jt::Vector2u getSizeForLine(
        std::shared_ptr<jt::renderTarget> const sptr, std::string const& text) const;

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const /*sptr*/) const override;

    void doRotate(float /*rot*/) override;

    void recreateTextTexture(std::shared_ptr<jt::renderTarget> const sptr);
    std::shared_ptr<jt::renderTarget> getRenderTarget();
    void setSDLColor(jt::Color const& col) const;
    SDL_Rect getDestRect(jt::Vector2 const& positionOffset = jt::Vector2 { 0.0f, 0.0f }) const;

    int getUpscaleFactor() const { return 1; };
    void calculateTextTextureSize(
        std::shared_ptr<jt::renderTarget> const sptr, std::vector<std::string> const& ssv);
};
} // namespace jt

#endif
