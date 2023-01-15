#include "drawable_impl_sdl.hpp"

SDL_BlendMode jt::DrawableImplSdl::getSDLBlendMode() const
{
    if (getBlendMode() == jt::BlendMode::ALPHA) {
        return SDL_BLENDMODE_BLEND;
    } else if (getBlendMode() == jt::BlendMode::ADD) {
        return SDL_BLENDMODE_ADD;
    } else if (getBlendMode() == jt::BlendMode::MUL) {
        return SDL_BLENDMODE_MOD;
    }
}

void jt::DrawableImplSdl::setOriginInternal(jt::Vector2f const& origin)
{
    m_offsetFromOrigin = -1.0f * jt::Vector2f { origin.x * getScale().x, origin.y * getScale().y };
}

jt::Vector2f jt::DrawableImplSdl::getCompleteCamOffset() const
{
    if (getIgnoreCamMovement()) {
        return getCamOffset() + m_camMovementFactor * getStaticCamOffset();
    } else {
        return getCamOffset();
    }
}
