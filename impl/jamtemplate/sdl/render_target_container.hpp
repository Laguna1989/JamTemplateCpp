#ifndef JAMTEMPLATE_RENDER_TARGET_CONTAINER_HPP
#define JAMTEMPLATE_RENDER_TARGET_CONTAINER_HPP

#include "graphics/render_target_container_interface.hpp"

namespace jt {

class RenderTargetContainer : public RenderTargetContainerInterface {
public:
    void forall(std::function<void(std::shared_ptr<jt::RenderTarget>)> func) override;
    std::shared_ptr<jt::RenderTarget> get(int z) override;
    void add(int z, std::shared_ptr<jt::RenderTarget> target) override;

    std::map<int, std::shared_ptr<jt::RenderTarget>> m_targets;
};
} // namespace jt

#endif // JAMTEMPLATE_RENDER_TARGET_CONTAINER_HPP
