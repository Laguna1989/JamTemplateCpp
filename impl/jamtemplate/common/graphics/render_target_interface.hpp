#ifndef JAMTEMPLATE_RENDER_TARGET_INTERFACE_HPP
#define JAMTEMPLATE_RENDER_TARGET_INTERFACE_HPP

#include <render_target.hpp>
#include <functional>
#include <map>
#include <memory>

namespace jt {

class RenderTargetInterface {
public:
    /// Get The RenderTargetLayer for a specific z value
    /// \param z the z value
    /// \return the RenderTargetLayer
    virtual std::shared_ptr<jt::RenderTargetLayer> get(int z) = 0;

    virtual ~RenderTargetInterface() = default;

    // no copy, no move. Avoid slicing.
    RenderTargetInterface(const RenderTargetInterface&) = delete;
    RenderTargetInterface(RenderTargetInterface&&) = delete;
    RenderTargetInterface& operator=(const RenderTargetInterface&) = delete;
    RenderTargetInterface& operator=(RenderTargetInterface&&) = delete;

protected:
    // default default constructor can only be called from derived classes
    RenderTargetInterface() = default;
};
} // namespace jt

#endif // JAMTEMPLATE_RENDER_TARGET_INTERFACE_HPP
