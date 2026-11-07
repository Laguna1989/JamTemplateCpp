#pragma once

#include <graphics/drawable_impl.hpp>

namespace jt {
class DrawableImplSdl : public jt::DrawableImpl {
public:
    SDL_BlendMode getSDLBlendMode() const noexcept;

    void setOriginInternal(jt::Vector2f const& origin) noexcept override;

    jt::Vector2f getCompleteCamOffset() const noexcept;

protected:
    jt::Vector2f m_offsetFromOrigin { 0.0f, 0.0f };
    jt::Vector2f m_scale { 1.0f, 1.0f };
};

} // namespace jt
