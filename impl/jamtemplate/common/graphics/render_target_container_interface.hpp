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
    virtual std::shared_ptr<jt::RenderTarget> get(int z) = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_RENDER_TARGET_CONTAINER_INTERFACE_HPP
