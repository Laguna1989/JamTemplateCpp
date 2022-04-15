#include "sfml_setup.hpp"
#include <texture_manager_impl.hpp>

std::shared_ptr<jt::RenderTarget> getRenderTarget() { return std::make_shared<jt::RenderTarget>(); }

jt::TextureManagerInterface& getTextureManager()
{
    static jt::TextureManagerImpl tm { getRenderTarget() };
    tm.reset();
    return tm;
}
