#ifndef JAMTEMPLATE_RENDER_TARGET_STUB_HPP
#define JAMTEMPLATE_RENDER_TARGET_STUB_HPP

#include <graphics/render_target_interface.hpp>
#include <memory>

/// Render target without any layers. Drawables drawn onto it return early.
class RenderTargetStub : public jt::RenderTargetInterface {
public:
    std::shared_ptr<jt::RenderTargetLayer> const& get(int /*z*/) override { return m_layer; }

private:
    std::shared_ptr<jt::RenderTargetLayer> m_layer { nullptr };
};

#endif // JAMTEMPLATE_RENDER_TARGET_STUB_HPP
