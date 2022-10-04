#ifndef JAMTEMPLATE_RENDER_TARGET_CONTAINER_HPP
#define JAMTEMPLATE_RENDER_TARGET_CONTAINER_HPP

#include <render_target.hpp>
#include <functional>
#include <map>
#include <memory>

namespace jt {
class RenderTargetContainer {
public:
    void forall(std::function<void(std::shared_ptr<jt::RenderTarget>)> func);
    std::map<int, std::shared_ptr<jt::RenderTarget>> m_targets;
};
} // namespace jt

#endif // JAMTEMPLATE_RENDER_TARGET_CONTAINER_HPP
