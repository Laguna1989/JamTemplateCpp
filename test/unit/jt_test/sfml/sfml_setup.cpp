#include "sfml_setup.hpp"
#include <render_target_container.hpp>
#include <texture_manager_impl.hpp>

std::shared_ptr<jt::RenderTarget> getRenderTarget() { return std::make_shared<jt::RenderTarget>(); }

std::shared_ptr<jt::RenderTargetContainerInterface> getRenderTargetContainer()
{
    auto target = std::make_shared<jt::RenderTargetContainer>();
    target->add(0, getRenderTarget());
    return target;
}

jt::TextureManagerInterface& getTextureManager()
{
    static jt::TextureManagerImpl tm { getRenderTarget() };
    tm.reset();
    return tm;
}
