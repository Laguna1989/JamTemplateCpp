#include "line.hpp"
#include <math_helper.hpp>
#include <sdl_2_include.hpp>

jt::Line::Line()
    : Line { jt::Vector2f { 0.0f, 0.0f } }
{
}

jt::Line::Line(jt::Vector2f lineVector)
    : m_lineVector { std::move(lineVector) }
    , m_color { jt::colors::White }
{
}

void jt::Line::setLineVector(jt::Vector2f const& lineVector) noexcept { m_lineVector = lineVector; }

jt::Vector2f jt::Line::getLineVector() const noexcept { return m_lineVector; }

void jt::Line::doUpdate(float /*elapsed*/) noexcept { }

void jt::Line::doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }

    auto const startPosition = getPosition() + getShakeOffset() + getOffset() + getCamOffset();
    auto const endPosition = startPosition + m_lineVector;

    SDL_SetRenderDrawColor(sptr.get(), m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderDrawLine(sptr.get(), static_cast<int>(startPosition.x),
        static_cast<int>(startPosition.y), static_cast<int>(endPosition.x),
        static_cast<int>(endPosition.y));
}

void jt::Line::doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }

    auto const startPosition = getPosition() + getShakeOffset() + getOffset() + getCamOffset();
    auto const endPosition = startPosition + m_lineVector;

    auto const flashColor = getFlashColor();
    SDL_SetRenderDrawColor(sptr.get(), flashColor.r, flashColor.g, flashColor.b, flashColor.a);
    SDL_RenderDrawLine(sptr.get(), static_cast<int>(startPosition.x),
        static_cast<int>(startPosition.y), static_cast<int>(endPosition.x),
        static_cast<int>(endPosition.y));
}

void jt::Line::doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }

    auto const startPosition
        = getPosition() + getShakeOffset() + getOffset() + getCamOffset() + getShadowOffset();
    auto const endPosition = startPosition + m_lineVector + getShadowOffset();

    SDL_SetRenderDrawColor(
        sptr.get(), getShadowColor().r, getShadowColor().g, getShadowColor().b, getShadowColor().a);
    SDL_RenderDrawLine(sptr.get(),
        // clang-format off
        static_cast<int>(startPosition.x), static_cast<int>(startPosition.y),
        static_cast<int>(endPosition.x), static_cast<int>(endPosition.y)
        // clang-format on
    );
}

void jt::Line::doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!sptr) [[unlikely]] {
        return;
    }

    auto const startPosition
        = getPosition() + getShakeOffset() + getOffset() + getCamOffset() + getShadowOffset();
    auto const endPosition = startPosition
        + jt::Vector2f { m_lineVector.x * m_scale.x, m_lineVector.y * m_scale.y }
        + getShadowOffset();

    SDL_SetRenderDrawColor(sptr.get(), getOutlineColor().r, getOutlineColor().g,
        getOutlineColor().b, getOutlineColor().a);
    for (auto const outlineOffset : getOutlineOffsets()) {
        SDL_RenderDrawLine(sptr.get(),
            // clang-format off
        static_cast<int>(startPosition.x + outlineOffset.x), static_cast<int>(startPosition.y + outlineOffset.y),
        static_cast<int>(endPosition.x + outlineOffset.x), static_cast<int>(endPosition.y + outlineOffset.y)
            // clang-format on
        );
    }
}

void jt::Line::doRotate(float d) noexcept
{
    m_lineVector = jt::MathHelper::rotateBy(m_lineVector, d);
}

void jt::Line::setColor(jt::Color const& col) noexcept { m_color = col; }

jt::Color jt::Line::getColor() const noexcept { return m_color; }

void jt::Line::setPosition(jt::Vector2f const& pos) noexcept { m_position = pos; }

jt::Vector2f jt::Line::getPosition() const noexcept { return m_position; }

jt::Rectf jt::Line::getGlobalBounds() const { return jt::Rectf {}; }

jt::Rectf jt::Line::getLocalBounds() const { return jt::Rectf {}; }

void jt::Line::setScale(jt::Vector2f const& scale)
{
    m_scale = scale;
    setOriginInternal(m_origin);
}

jt::Vector2f jt::Line::getScale() const { return m_scale; }
