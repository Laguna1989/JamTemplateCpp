#ifndef JAMTEMPLATE_RENDER_TARGET_LIB_HPP
#define JAMTEMPLATE_RENDER_TARGET_LIB_HPP

#include <graphics/render_target_interface.hpp>

namespace jt {

class RenderTarget : public RenderTargetInterface {
public:
    std::shared_ptr<jt::RenderTargetLayer> get(int z) override;

    void forall(std::function<void(std::shared_ptr<jt::RenderTargetLayer>&)> const& func);
    void add(int z, std::shared_ptr<jt::RenderTargetLayer> target);
    void clearPixels() const;

private:
    std::map<int, std::shared_ptr<jt::RenderTargetLayer>> m_targets;
};

} // namespace jt

#endif // JAMTEMPLATE_RENDER_TARGET_LIB_HPP
