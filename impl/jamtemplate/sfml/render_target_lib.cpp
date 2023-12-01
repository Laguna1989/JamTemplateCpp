#include "render_target_lib.hpp"

void jt::RenderTarget::forall(
    std::function<void(std::shared_ptr<jt::RenderTargetLayer>&)> const& func)
{
    for (auto& kvp : m_targets) {
        func(kvp.second);
    }
}

std::shared_ptr<jt::RenderTargetLayer> jt::RenderTarget::get(int z) { return m_targets[z]; }

void jt::RenderTarget::add(int z, std::shared_ptr<jt::RenderTargetLayer> target)
{
    m_targets[z] = target;
}

void jt::RenderTarget::clearPixels() const
{
    bool first { true };

    for (auto const& kvp : m_targets) {
        if (first) {
            kvp.second->clear(sf::Color::Black);
            first = false;
        } else {
            kvp.second->clear(sf::Color::Transparent);
        }
    }
}
