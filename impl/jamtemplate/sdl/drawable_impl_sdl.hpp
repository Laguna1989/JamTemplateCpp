#ifndef GUARD_JAMTEMPLATE_DRAWABLE_IMPL_SDL_HPP
#define GUARD_JAMTEMPLATE_DRAWABLE_IMPL_SDL_HPP

#include "graphics/drawable_impl.hpp"

namespace jt {
class DrawableImplSdl : public jt::DrawableImpl {
public:
    void setCustomShader(
        std::string const& shaderCodeVertex, std::string const& shaderCodeFragment) override;
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_DRAWABLE_IMPL_SDL_HPP
