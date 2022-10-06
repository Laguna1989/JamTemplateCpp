#ifndef JAMTEMPLATE_RENDER_TARGET_INTERFACE_HPP
#define JAMTEMPLATE_RENDER_TARGET_INTERFACE_HPP

#include <render_target.hpp>
#include <functional>
#include <map>
#include <memory>

namespace jt {

class RenderTargetInterface {
public:
    virtual ~RenderTargetInterface() = default;

    /// Get The RenderTargetLayer for a specific z value
    /// \param z the z value
    /// \return the RenderTargetLayer
    virtual std::shared_ptr<jt::RenderTargetLayer> get(int z) = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_RENDER_TARGET_INTERFACE_HPP
