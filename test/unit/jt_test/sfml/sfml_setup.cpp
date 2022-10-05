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
    static jt::TextureManagerImpl tm { getRenderTarget() };
    tm.reset();
    return tm;
}
