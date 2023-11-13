#include "sfml_setup.hpp"
#include <render_target_lib.hpp>
#include <texture_manager_impl.hpp>

std::shared_ptr<jt::RenderTargetLayer> getRenderTarget()
{
    return std::make_shared<jt::RenderTargetLayer>();
}

std::shared_ptr<jt::RenderTargetInterface> getRenderTargetContainer()
{
    auto target = std::make_shared<jt::RenderTarget>();
    target->add(0, getRenderTarget());
    return target;
}

jt::TextureManagerInterface& getTextureManager()
{
    // the sfml texture manager does not need a render target. Passing nullptr is fine here.
    static jt::TextureManagerImpl tm { nullptr };
    tm.reset();
    return tm;
}
