#ifndef GUARD_JAMTEMPLATE_SMARTTEXT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTTEXT_HPP_INCLUDEGUARD

#include "SmartDrawable.hpp"
#include "rendertarget.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <string>
#include <vector>

namespace jt {

class SmartText : public SmartDrawable {
public:
    enum class TextAlign { CENTER, LEFT, RIGHT };

    using Sptr = std::shared_ptr<SmartText>;

    virtual ~SmartText();

    void loadFont(std::string const& fontFileName, unsigned int characterSize,
        std::weak_ptr<jt::renderTarget> wptr);

    void setText(std::string const& text);
    std::string getText() const;

    void setOutline(float /*thickness*/, jt::color /*col*/);

    void setPosition(jt::vector2 const& pos) override;

    const jt::vector2 getPosition() const override;

    void setColor(const jt::color& col) override;
    const jt::color getColor() const override;

    void setFlashColor(const jt::color& col) override;
    const jt::color getFlashColor() const override;

    // virtual sf::Transform const getTransform() const override { return m_text->getTransform(); }

    jt::rect const getGlobalBounds() const override;
    jt::rect const getLocalBounds() const override;

    virtual void setScale(jt::vector2 const& scale) override;

    virtual const jt::vector2 getScale() const override;

    virtual void setOrigin(jt::vector2 const& origin) override;

    virtual jt::vector2 const getOrigin() const override;

    void SetTextAlign(TextAlign ta);
    TextAlign getTextAlign() const;

private:
    TTF_Font* m_font { nullptr };
    std::string m_text { "" };

    TextAlign m_textAlign { TextAlign::CENTER };

    jt::vector2 m_position { 0, 0 };
    jt::color m_color { jt::colors::White };
    jt::color m_flashColor { jt::colors::White };
    jt::vector2 m_origin { 0.0f, 0.0f };
    jt::vector2 m_scale { 1.0f, 1.0f };

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

    jt::vector2u getSizeForLine(
        std::shared_ptr<jt::renderTarget> const sptr, std::string const& text) const;

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const /*sptr*/) const override;

    void doRotate(float /*rot*/) override;

    void recreateTextTexture(std::shared_ptr<jt::renderTarget> const sptr);
    std::shared_ptr<jt::renderTarget> getRenderTarget();
    void setSDLColor(jt::color const& col) const;
    SDL_Rect getDestRect(jt::vector2 const& positionOffset = jt::vector2 { 0.0f, 0.0f }) const;

    int getUpscaleFactor() const { return 5; };
    void calculateTextTextureSize(
        std::shared_ptr<jt::renderTarget> const sptr, std::vector<std::string> const& ssv);
};
} // namespace jt

#endif
