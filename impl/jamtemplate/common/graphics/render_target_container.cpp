
#include "render_target_container.hpp"

void jt::RenderTargetContainer::forall(std::function<void(std::shared_ptr<jt::RenderTarget>)> func)
{
    for (auto& kvp : m_targets) {
        func(kvp.second);
    }
}
