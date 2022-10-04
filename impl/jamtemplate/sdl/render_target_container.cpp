
#include "render_target_container.hpp"

void jt::RenderTargetContainer::forall(std::function<void(std::shared_ptr<jt::RenderTarget>)> func)
{
    for (auto& kvp : m_targets) {
        func(kvp.second);
    }
}

std::shared_ptr<jt::RenderTarget> jt::RenderTargetContainer::get(int z) { return m_targets[z]; }

void jt::RenderTargetContainer::add(int z, std::shared_ptr<jt::RenderTarget> target)
{
    m_targets[z] = target;
}
