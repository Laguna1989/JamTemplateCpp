#include "drawable_impl_sdl.hpp"

void jt::DrawableImplSdl::setCustomShader(
    std::string const& shaderCodeVertex, std::string const& shaderCodeFragment)
{
}

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
