#ifndef JAMTEMPLATE_DRAWABLE_IMPL_SDL_HPP
#define JAMTEMPLATE_DRAWABLE_IMPL_SDL_HPP

#include <graphics/drawable_impl.hpp>

namespace jt {
class DrawableImplSdl : public jt::DrawableImpl {
public:
    [[deprecated("Currently only implemented for SFML")]] void setCustomShader(
        std::string const& shaderCodeVertex, std::string const& shaderCodeFragment) override;
    SDL_BlendMode getSDLBlendMode() const;
};

} // namespace jt

#endif // JAMTEMPLATE_DRAWABLE_IMPL_SDL_HPP
