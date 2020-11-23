#ifndef JAMTEMPLATE_SMARTSHAPE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTSHAPE_HPP_INCLUDEGUARD

#include "SmartObject.hpp"
#include "rect.hpp"
#include "rendertarget.hpp"
#include "vector.hpp"
#include <SDL.h>
#include <memory>
#include <string>

namespace JamTemplate {
class SmartShape : public SmartObject {
public:
    using Sptr = std::shared_ptr<SmartShape>;

    void makeRect(jt::vector2 size)
    {
        m_shape = std::make_shared<jt::rect>(0, 0, size.x(), size.y());
        m_color = jt::colors::White;
        m_flashColor = jt::colors::White;
    }

    void setColor(jt::color const& col) override { m_color = col; }
    const jt::color getColor() const override { return m_color; }

    void setFlashColor(jt::color const& col) override { m_flashColor = col; }
    const jt::color getFlashColor() const override { return m_flashColor; }

    void setPosition(jt::vector2 const& pos) override { m_position = pos; }
    const jt::vector2 getPosition() const override { return m_position; }

    // sf::Transform const getTransform() const override { return m_shape->getTransform(); }
    jt::rect const getGlobalBounds() const override
    {
        // TODO
        return jt::rect {};
    }
    jt::rect const getLocalBounds() const override
    {
        // TODO
        return jt::rect {};
    }

    std::shared_ptr<jt::rect> getShape() { return m_shape; }

    void setScale(jt::vector2 const& scale) override
    {
        // TODO
    }
    const jt::vector2 getScale() const override { return jt::vector2 {}; }

    void setOrigin(jt::vector2 const& origin) override
    {
        // TODO
        // m_shape->setOrigin(origin);
    }
    const jt::vector2 getOrigin() const override
    {
        // TODO
        return jt::vector2 {};
    }

private:
    mutable std::shared_ptr<jt::rect> m_shape = nullptr;
    jt::color m_color;
    jt::color m_flashColor;

    jt::vector2 m_position { 0, 0 };

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        SDL_SetRenderDrawColor(sptr.get(), m_color.r(), m_color.g(), m_color.b(), m_color.a());
        SDL_Rect rect { static_cast<int>(m_shape->top()), static_cast<int>(m_shape->left()),
            static_cast<int>(m_shape->width()), static_cast<int>(m_shape->height()) };
        SDL_RenderFillRect(sptr.get(), &rect);
    }

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        SDL_SetRenderDrawColor(
            sptr.get(), m_flashColor.r(), m_flashColor.g(), m_flashColor.b(), m_flashColor.a());
        SDL_Rect rect { static_cast<int>(m_shape->top()), static_cast<int>(m_shape->left()),
            static_cast<int>(m_shape->width()), static_cast<int>(m_shape->height()) };
        SDL_RenderFillRect(sptr.get(), &rect);
    }

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override
    {
        SDL_SetRenderDrawColor(sptr.get(), getShadowColor().r(), getShadowColor().g(),
            getShadowColor().b(), getShadowColor().a());
        SDL_Rect rect { static_cast<int>(m_shape->top() + +getShadowOffset().x()),
            static_cast<int>(m_shape->left() + getShadowOffset().y()),
            static_cast<int>(m_shape->width()), static_cast<int>(m_shape->height()) };
        SDL_RenderFillRect(sptr.get(), &rect);
    }

    void doUpdate(float /*elapsed*/) override
    {
        auto const pos = getPosition() + getShakeOffset() + getOffset() + getCamOffset();
        m_shape->left() = pos.x();
        m_shape->top() = pos.y();
    }

    void doRotate(float rot) override
    {
        // m_shape->setRotation(-rot);
    }
};
} // namespace JamTemplate

#endif
