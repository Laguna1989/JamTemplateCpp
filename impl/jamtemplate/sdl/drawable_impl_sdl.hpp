#ifndef JAMTEMPLATE_DRAWABLE_IMPL_SDL_HPP
#define JAMTEMPLATE_DRAWABLE_IMPL_SDL_HPP

#include <graphics/drawable_impl.hpp>

namespace jt {
class DrawableImplSdl : public jt::DrawableImpl {
public:
    [[deprecated("Currently only implemented for SFML")]] void setCustomShader(
        std::string const& shaderCodeVertex, std::string const& shaderCodeFragment) override;
    SDL_BlendMode getSDLBlendMode() const;

    void setOriginInternal(jt::Vector2f const& origin) override;

protected:
    jt::Vector2f m_offsetFromOrigin { 0.0f, 0.0f };
};

} // namespace jt

#endif // JAMTEMPLATE_DRAWABLE_IMPL_SDL_HPP
