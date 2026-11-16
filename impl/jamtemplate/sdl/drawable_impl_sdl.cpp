#include "drawable_impl_sdl.hpp"
#include <cmath>

SDL_BlendMode jt::DrawableImplSdl::getSDLBlendMode() const noexcept
{
    if (getBlendMode() == jt::BlendMode::ALPHA) {
        return SDL_BLENDMODE_BLEND;
    } else if (getBlendMode() == jt::BlendMode::ADD) {
        return SDL_BLENDMODE_ADD;
    } else if (getBlendMode() == jt::BlendMode::MUL) {
        return SDL_BLENDMODE_MOD;
    }
    return SDL_BLENDMODE_ADD;
}

void jt::DrawableImplSdl::setOriginInternal(jt::Vector2f const& origin) noexcept
{
    m_offsetFromOrigin = -1.0f * jt::Vector2f { origin.x * getScale().x, origin.y * getScale().y };
}

void jt::DrawableImplSdl::updateOffsetFromOrigin(
    jt::Vector2f const& origin, jt::Vector2f const& unscaledSize) noexcept
{
    auto const scale = getScale();
    auto const originX = scale.x < 0.0f ? unscaledSize.x - origin.x : origin.x;
    auto const originY = scale.y < 0.0f ? unscaledSize.y - origin.y : origin.y;
    m_offsetFromOrigin
        = -1.0f * jt::Vector2f { originX * std::fabs(scale.x), originY * std::fabs(scale.y) };
}

SDL_Point jt::DrawableImplSdl::getRotationPivot() const noexcept
{
    return SDL_Point { static_cast<int>(-m_offsetFromOrigin.x),
        static_cast<int>(-m_offsetFromOrigin.y) };
}

jt::Vector2f jt::DrawableImplSdl::getCompleteCamOffset() const noexcept
{
    if (getIgnoreCamMovement()) {
        return getCamOffset() + m_camMovementFactor * getStaticCamOffset();
    } else {
        return getCamOffset();
    }
}
