#ifndef JAMTEMPLATE_RENDER_TARGET_CONTAINER_INTERFACE_HPP
#define JAMTEMPLATE_RENDER_TARGET_CONTAINER_INTERFACE_HPP

#include <render_target.hpp>
#include <functional>
#include <map>
#include <memory>

namespace jt {

class RenderTargetContainerInterface {
public:
    virtual ~RenderTargetContainerInterface() = default;
    virtual void forall(std::function<void(std::shared_ptr<jt::RenderTarget>)> func) = 0;
    virtual std::shared_ptr<jt::RenderTarget> get(int z) = 0;

    virtual void add(int z, std::shared_ptr<jt::RenderTarget> target) = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_RENDER_TARGET_CONTAINER_INTERFACE_HPP
